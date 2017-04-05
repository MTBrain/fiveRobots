////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include "MsgHandlingSystem.h"
using namespace std;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	
	ModelClass(vMHS*);
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*,MHS,WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);


	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	


private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();


	bool LoadModel(char*);
	void ReleaseModel();

	bool createModel(MHS);
	void createRectangle(D3DXVECTOR3, D3DXVECTOR3, VertexType*, unsigned long*);

	vMHS* m_vmhs;

private:

	VertexType* m_vertices;
	unsigned long* m_indices;

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	ModelType* m_model;
};

#endif