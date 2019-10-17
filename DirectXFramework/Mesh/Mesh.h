#pragma once
//#include 
#include "../DXManager.h"
#include "../Framework.h"



class Mesh : virtual public Component
{
public:
	ShaderPointers shaderPointers;

	ID3D11Buffer*           g_pVertexBuffer = NULL;		// ����� ������
	ID3D11Buffer*           g_pIndexBuffer = NULL;		// ����� �������� ������
	ID3D11Buffer*           g_pConstantBuffer = NULL;	// ����������� �����
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
	XMFLOAT3 Pos;	// ���������� ����� � ������������
	XMFLOAT4 Color;	// ������ ������ ������� ����� ��������� ���������� � �����
};

struct TexturedVertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 TexPos;
};

struct ConstantBuffer
{
	XMMATRIX mWorld;		// ������� ����
	XMMATRIX mView;			// ������� ����
	XMMATRIX mProjection;	// ������� ��������
};

struct ConstantBufferUI
{
	XMMATRIX mWorld;		// ������� ����
	XMMATRIX mProjection;	// ������� ��������
};