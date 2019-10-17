#pragma once
//#include 
#include "../DXManager.h"
#include "../Framework.h"



class Mesh : virtual public Component
{
public:
	ShaderPointers shaderPointers;

	ID3D11Buffer*           g_pVertexBuffer = NULL;		// Буфер вершин
	ID3D11Buffer*           g_pIndexBuffer = NULL;		// Буфер индексов вершин
	ID3D11Buffer*           g_pConstantBuffer = NULL;	// Константный буфер
	WORD * Indices;
	int NumOfIndexes;
	int NumOfVerteces;

	virtual D3D11_INPUT_ELEMENT_DESC* layout() = 0;
	virtual UINT NumberOfElements() = 0;


	HRESULT InitShader(std::string ShaderName);
	virtual HRESULT InitMesh() = 0;

	virtual void process() = 0;
};

struct SimpleVertex
{
	XMFLOAT3 Pos;	// Координаты точки в пространстве
	XMFLOAT4 Color;	// Теперь каждая вершина будет содержать информацию о цвете
};

struct TexturedVertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 TexPos;
};

struct ConstantBuffer
{
	XMMATRIX mWorld;		// Матрица мира
	XMMATRIX mView;			// Матрица вида
	XMMATRIX mProjection;	// Матрица проекции
};

struct ConstantBufferUI
{
	XMMATRIX mWorld;		// Матрица мира
	XMMATRIX mProjection;	// Матрица проекции
};