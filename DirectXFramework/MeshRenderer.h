#pragma once
#include "Component.h"
#include "Framework.h"

class Camera;

class MeshRenderer : virtual public Component
{
	DXManager* dxmanager;
	int NumOfIndexes;
	int NumOfVerteces;

	ID3D11Buffer*           g_pVertexBuffer = NULL;		// ����� ������
	ID3D11Buffer*           g_pIndexBuffer = NULL;		// ����� �������� ������
	ID3D11Buffer*           g_pConstantBuffer = NULL;	// ����������� �����
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


