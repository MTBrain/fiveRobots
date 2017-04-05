////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"


ModelClass::ModelClass(vMHS* in)
{
	m_vmhs = in;

	m_vertexBuffer = 0;
	m_indexBuffer = 0;

	m_Texture = 0;
	m_model = 0;

	m_creature = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}


bool ModelClass::Initialize(ID3D11Device* device, MHS modelDef, WCHAR* textureFilename)
{
	bool result;

	result = createModel(modelDef);
	if (!result)
	{
		return false;
	}
	
	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if(!result)
	{
		MessageBoxA(NULL, "failed to ini Model Buffers", "modelclass.cpp", MB_OK);
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	

	return true;
}


void ModelClass::Shutdown()
{
	// Release the model texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}


ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}


bool ModelClass::InitializeBuffers(ID3D11Device* device)
{

	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;
/*

	// Create the vertex array.
	m_vertices = new VertexType[m_vertexCount];
	if(!m_vertices)
	{
		return false;
	}

	// Create the index array.
	m_indices = new unsigned long[m_indexCount];
	if(!m_indices)
	{
		return false;
	}

	// Load the vertex array and index array with data.
	for(i=0; i<m_vertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

		indices[i] = i;
	}
	*/

	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = m_vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = m_indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] m_vertices;
	m_vertices = 0;

	delete [] m_indices;
	m_indices = 0;

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


bool ModelClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if(!result)
	{
		return false;
	}

	return true;
}


void ModelClass::ReleaseTexture()
{
	// Release the texture object.
	if(m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}


bool ModelClass::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;


	// Open the model file.
	fin.open(filename);
	
	// If it could not open the file then exit.
	if(fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if(!m_model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for(i=0; i<m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	return true;
}


void ModelClass::ReleaseModel()
{
	if(m_model)
	{
		delete [] m_model;
		m_model = 0;
	}

	return;
}

bool ModelClass::createModel(MHS in)
{
	

	int switchvar = in.msg;
	switch (switchvar)
	{
	case 1:
		m_vertices = new VertexType[80];
		m_indices = new unsigned long[360];

		unsigned long asd[360];
		
		m_indexCount = 360;
		m_vertexCount = 80;
		
		createRectangle(D3DXVECTOR3(2, 10, 2.5), D3DXVECTOR3(4, 9, .5), &m_vertices[0], &m_indices[0]);		//head
		

		createRectangle(D3DXVECTOR3(1.5, 8.5, 3), D3DXVECTOR3(4.5, 4.5, 0), &m_vertices[8], &m_indices[36]);		//body
		for (int i = 0; i < 36; i++)
		{
			m_indices[36+i] += 8;
		}

		createRectangle(D3DXVECTOR3(0, 8.25, 1), D3DXVECTOR3(1, 5.25, 2), &m_vertices[16], &m_indices[72]);			//right arm
		for (int i = 0; i < 36; i++)
		{
			m_indices[72 + i] += 16;
		}
		createRectangle(D3DXVECTOR3(0.125, 5, 1), D3DXVECTOR3(0.875, 3, 1.75), &m_vertices[24], &m_indices[108]);
		for (int i = 0; i < 36; i++)
		{
			m_indices[108 + i] += 24;
		}

		
		createRectangle(D3DXVECTOR3(5, 8.25, 1), D3DXVECTOR3(6, 5.25, 2), &m_vertices[32], &m_indices[144]);			//left arm
		for (int i = 0; i < 36; i++)
		{
			m_indices[144 + i] += 32;
		}
		createRectangle(D3DXVECTOR3(5.125, 5, 1), D3DXVECTOR3(5.875, 3, 1.75), &m_vertices[40], &m_indices[180]);
		for (int i = 0; i < 36; i++)
		{
			m_indices[180 + i] += 40;
		}

		createRectangle(D3DXVECTOR3(1.5, 4, 0.875), D3DXVECTOR3(2.75, 2, 2.125), &m_vertices[48], &m_indices[216]); // right leg
		for (int i = 0; i < 36; i++)
		{
			m_indices[216 + i] += 48;
		}


		createRectangle(D3DXVECTOR3(1.5, 1.75, 0.875), D3DXVECTOR3(2.75, 0, 2.125), &m_vertices[56], &m_indices[252]);
		for (int i = 0; i < 36; i++)
		{
			m_indices[252 + i] += 56;
		}

		createRectangle(D3DXVECTOR3(3.25, 4, 0.875), D3DXVECTOR3(4.5, 2, 2.125), &m_vertices[32], &m_indices[288]); // left leg
		for (int i = 0; i < 36; i++)
		{
			m_indices[288 + i] += 64;
		}
		createRectangle(D3DXVECTOR3(3.25, 1.75, 0.875), D3DXVECTOR3(4.5, 0, 2.125), &m_vertices[32], &m_indices[324]);
		for (int i = 0; i < 36; i++)
		{
			m_indices[324 + i] += 72;
		}

		return true;

	case 2:
		m_vertices = new VertexType[8];
		m_indices = new unsigned long[36];
		m_indexCount = 36;
		m_vertexCount = 8;
		createRectangle(D3DXVECTOR3(-1,1,1),D3DXVECTOR3(1, -1, -1),m_vertices,m_indices);
		return true;
		
	case 3:
		UINT ov = 0;
		UINT oi = 0;

		UINT circleVertices = 12;

		if (!m_creature)
		{
			m_creature = new CreatureClass(3, 2);
		}
		m_vertices =(VertexType*) malloc(m_creature->nodeCount*circleVertices + m_creature->muscleCount * 4);
		m_indices = (unsigned long*)malloc(m_creature->nodeCount*circleVertices * 3 + m_creature->muscleCount * 6);
		for (int i = 0; i < m_creature->nodeCount; i++)
		{
			createCircle(D3DXVECTOR3(m_creature->nodes[i]->posX, m_creature->nodes[i]->posY, 0.0), m_creature->nodes[i]->size, m_vertices, m_indices, circleVertices,oi,ov);
			ov += circleVertices;
			oi += 3 * circleVertices;
		}
		for (int i = 0; i < m_creature->muscleCount; i++)
		{
			createRectangle2D(D3DXVECTOR3(m_creature->nodes[m_creature->muscles[i]->node1]->posX, m_creature->nodes[m_creature->muscles[i]->node1]->posY + MUSCLE_RELATIVE_SIZE * m_creature->nodes[m_creature->muscles[i]->node2]->size, -0.1f),
				D3DXVECTOR3(m_creature->nodes[m_creature->muscles[i]->node2]->posX, m_creature->nodes[m_creature->muscles[i]->node2]->posY - MUSCLE_RELATIVE_SIZE * m_creature->nodes[m_creature->muscles[i]->node2]->size, -0.1),
				m_vertices, m_indices,oi,ov);
			ov += 4;
			oi += 6;
		}
		m_vertexCount = ov;
		m_indexCount = oi;

		return true;

	}

	return true;
}

void ModelClass::createRectangle(D3DXVECTOR3 tlb, D3DXVECTOR3 brf, VertexType* v8o, unsigned long* i36o)
{
	VertexType v[8];

	int width = tlb.x - brf.x;
	int height = tlb.y - brf.y;
	int depth = tlb.z - brf.z;

	v[0].position.x = tlb.x;
	v[0].position.y = tlb.y;
	v[0].position.z = tlb.z;

	v[1].position.x = tlb.x - width;
	v[1].position.y = tlb.y;
	v[1].position.z = tlb.z;

	v[2].position.x = tlb.x;
	v[2].position.y = tlb.y - height;
	v[2].position.z = tlb.z;

	v[3].position.x = tlb.x - width;
	v[3].position.y = tlb.y - height;
	v[3].position.z = tlb.z;


	v[4].position.x = brf.x;
	v[4].position.y = brf.y;
	v[4].position.z = brf.z;

	v[5].position.x = brf.x + width;
	v[5].position.y = brf.y;
	v[5].position.z = brf.z;

	v[6].position.x = brf.x;
	v[6].position.y = brf.y + height;
	v[6].position.z = brf.z;

	v[7].position.x = brf.x + width;
	v[7].position.y = brf.y + height;
	v[7].position.z = brf.z;


	D3DXVECTOR3 cen;

	cen.x = tlb.x + (brf.x - tlb.x)/2;
	cen.y = tlb.y + (brf.y - tlb.y)/2;
	cen.z = tlb.z + (brf.z - tlb.z)/2;

	for (int i = 0; i < 8; i++)
	{
		v[i].normal.x = v[i].position.x - cen.x;
		v[i].normal.y = v[i].position.y - cen.y;
		v[i].normal.z = v[i].position.z - cen.z;

		v[i].texture.x = 0;
		v[i].texture.y = 0;
	}

	unsigned long ind[36] = {0,1,5, 0,5,4, 0,2,1, 2,1,3, 5,7,3, 5,3,1, 2,7,3, 2,7,6, 4,2,6, 4,2,0, 4,7,6, 4,7,5};
	
	for (int i = 0; i < 8; i++)
	{
		v8o[i] = v[i];
	}

	for (int i = 0; i < 36; i++)
	{
		i36o[i] = ind[i]; 
	}
}
/*
	3 * vertices -> index
	vertices -> vertices
*/
void ModelClass::createCircle(D3DXVECTOR3 tlb, double r, VertexType* vertexbuffer, unsigned long* indexbuffer ,int vertices,UINT oi ,UINT ov)
{
	double step = 2 * M_PI / vertices;

	for (int i = 0; i < vertices; i++)
	{
		vertexbuffer[i + ov].normal = D3DXVECTOR3(0.0, 0.0, 1.0);
		vertexbuffer[i + ov].position = D3DXVECTOR3(cos(step*i), sin(step*i), 0.0);
		vertexbuffer[i + ov].texture = D3DXVECTOR2(0.0, 0.0);
	}
	for (int i = 0; i < vertices - 2; i++)
	{
		indexbuffer[3 * i + oi] = 0;
		indexbuffer[3 * i + 1 + oi] = i + 1;
		indexbuffer[3 * i + 2 + oi] = i + 2;
	}
}

void ModelClass::createRectangle2D(D3DXVECTOR3 tlb, D3DXVECTOR3 brf, VertexType* v4, unsigned long* i6,UINT oi, UINT ov)
{
	v4[ov + 0].position = tlb;
	v4[ov + 0].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	v4[ov + 0].texture = D3DXVECTOR2(0.0f, 0.0f);

	v4[ov + 1].position = tlb;
	v4[ov + 1].position.x = brf.x;
	v4[ov + 1].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	v4[ov + 1].texture = D3DXVECTOR2(0.0f, 0.0f);

	v4[ov + 2].position = brf;
	v4[ov + 2].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	v4[ov + 2].texture = D3DXVECTOR2(0.0f, 0.0f);

	v4[ov + 3].position = brf;
	v4[ov + 3].position.x = tlb.x;
	v4[ov + 3].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	v4[ov + 3].texture = D3DXVECTOR2(0.0f, 0.0f);
	
	i6[oi + 0] = 0;
	i6[oi + 1] = 1;
	i6[oi + 2] = 3;
	i6[oi + 3] = 3;
	i6[oi + 4] = 1;
	i6[oi + 5] = 2;

}

