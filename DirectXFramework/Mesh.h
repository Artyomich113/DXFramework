#pragma once
#include "Component.h"
#include "DXManager.h"
#include "Framework.h"

class Mesh : virtual public Component
{
public:
	ShaderPointers shaderPointers;

	ID3D11Buffer*           g_pVertexBuffer = NULL;		// Буфер вершин
	ID3D11Buffer*           g_pIndexBuffer = NULL;		// Буфер индексов вершин
	ID3D11Buffer*           g_pConstantBuffer = NULL;	// Константный буфер

	int NumOfIndexes;
	int NumOfVerteces;

	virtual D3D11_INPUT_ELEMENT_DESC* layout() = 0;
	virtual UINT NumberOfElements() = 0;


	HRESULT InitShader(std::string ShaderName);
	virtual HRESULT InitMesh() = 0;

	virtual void process() = 0;
};