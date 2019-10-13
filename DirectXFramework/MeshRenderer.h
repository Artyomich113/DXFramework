#pragma once
#include "Component.h"
#include "Framework.h"

class Camera;

class MeshRenderer : virtual public Component
{
	DXManager* dxmanager;
	int NumOfIndexes;
	int NumOfVerteces;

	ID3D11Buffer*           g_pVertexBuffer = NULL;		// Буфер вершин
	ID3D11Buffer*           g_pIndexBuffer = NULL;		// Буфер индексов вершин
	ID3D11Buffer*           g_pConstantBuffer = NULL;	// Константный буфер
public:
	Layout ComponentType(){return Layout::Render;};
	MeshRenderer(const MeshRenderer&);
	HRESULT InitShader(std::string);

	HRESULT InitMesh();
	std::string ShaderName;

	SimpleVertex *Vertices;
	WORD * Indices;

	MeshRenderer(SimpleVertex*,WORD*, /*std::string,*/int indexes,int verteces);
	//void SetVertexes(SimpleVertex);
	//void SetIndexes(WORD);
	~MeshRenderer();
	void process();
};


