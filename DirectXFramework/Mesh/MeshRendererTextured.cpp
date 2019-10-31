#include "MeshRendererTextured.h"

MeshRendererTextured::MeshRendererTextured(const MeshRendererTextured &ob)
{
	NumOfIndexes = ob.NumOfIndexes;
	NumOfVerteces = ob.NumOfVerteces;

	g_pVertexBuffer = ob.g_pVertexBuffer;
	g_pIndexBuffer = ob.g_pIndexBuffer;
	g_pConstantBuffer = ob.g_pConstantBuffer;

	g_pTextureRV = ob.g_pTextureRV;
	g_pSamplerLinear = ob.g_pSamplerLinear;

	shaderPointers = ob.shaderPointers;
	dxmanager = Framework::instanse().GetDXManager();
	copy = true;
}

HRESULT MeshRendererTextured::InitMesh()
{
	std::cout << "\ninit mesh";
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC bd;	// Структура, описывающая создаваемый буфер
	//std::cout << "\nzero memory";
	ZeroMemory(&bd, sizeof(bd));				// очищаем ее
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(TexturedVertex) * NumOfVerteces;	// размер буфера
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// тип буфера - буфер вершин
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;	// Структура, содержащая данные буфера
	//std::cout << "\nzero memory";
	ZeroMemory(&InitData, sizeof(InitData));	// очищаем ее
	InitData.pSysMem = Vertices;				// указатель на наши 8 вершин
	// Вызов метода g_pd3dDevice создаст объект буфера вершин
	//std::cout << "\n   createbuffer";
	hr = dxmanager->m_device->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
	//std::cout << "\n   buffer created";
	if (FAILED(hr))
	{
		std::cout << "\n  failed create vertices buffer " << NumOfVerteces << " vecteces";
		return hr;
	}

	bd.Usage = D3D11_USAGE_DEFAULT;		// Структура, описывающая создаваемый буфер
	bd.ByteWidth = sizeof(WORD) * NumOfIndexes;	// для 6 треугольников необходимо 18 вершин
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER; // тип - буфер индексов
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = Indices;				// указатель на наш массив индексов
	// Вызов метода g_pd3dDevice создаст объект буфера индексов
	//std::cout << "\n    creating indeces buffer";
	hr = dxmanager->m_device->CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
	if (FAILED(hr))
	{
		std::cout << "\nfailed create indices buffer";
		return hr;
	}


	dxmanager->m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Создание константного буфера
	bd.Usage = D3D11_USAGE_DEFAULT;

	bd.ByteWidth = sizeof(ConstantBuffer);		// размер буфера = размеру структуры
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// тип - константный буфер
	bd.CPUAccessFlags = 0;

	hr = dxmanager->m_device->CreateBuffer(&bd, NULL, &g_pConstantBuffer);
	if (FAILED(hr))
	{
		std::cout << "\nfailed create costant buffer";
		return hr;
	}

	hr = D3DX11CreateShaderResourceViewFromFile(dxmanager->m_device, TextureName.c_str(), NULL, NULL, &g_pTextureRV, NULL);
	if (FAILED(hr))
	{
		std::cout << "\n failed createShaderResourceView";
		return hr;
	}

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;	// Тип фильтрации
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;//D3D11_TEXTURE_ADDRESS_WRAP;		
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;//D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = 10;//D3D11_FLOAT32_MAX;
	// Создаем интерфейс сэмпла текстурирования
	hr = dxmanager->m_device->CreateSamplerState(&sampDesc, &g_pSamplerLinear);
	if (FAILED(hr))
	{
		std::cout << "\nfailed create sample state";
		return hr;
	}
	std::cout << "\ninit mesh/";
	return hr;
}

MeshRendererTextured::MeshRendererTextured(std::string TextureName, TexturedVertex *vertices, WORD* indices, int NumberOfIndexes, int NumberOfVerteces)
{
	//std::cout << " new meh Renderer Textured";
	Vertices = vertices;
	Indices = indices;
	this->NumOfIndexes = NumberOfIndexes;
	this->NumOfVerteces = NumberOfVerteces;
	dxmanager = Framework::instanse().GetDXManager();
	this->TextureName = TextureName;
}

D3D11_INPUT_ELEMENT_DESC * MeshRendererTextured::layout()
{
	D3D11_INPUT_ELEMENT_DESC * layout = new D3D11_INPUT_ELEMENT_DESC[2];

	layout[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	layout[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	//{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	return layout;
}

UINT MeshRendererTextured::NumberOfElements()
{
	return (UINT)2;
}

MeshRendererTextured::~MeshRendererTextured()
{
	std::cout << "\n~MeshRendererTextured";
	if (g_pSamplerLinear)g_pSamplerLinear->Release();
	if (g_pTextureRV)g_pTextureRV->Release();
}

void MeshRendererTextured::process()
{
	std::cout << "\nTextMR";
	XMMATRIX mRotation = XMMatrixRotationQuaternion(gameobject->transform->Rotation);
	//XMMATRIX mRotation = XMMatrixRotationRollPitchYawFromVector(gameobject->transform->Rotation);

	XMMATRIX mTranslate = XMMatrixTranslationFromVector(gameobject->transform->Position);

	XMMATRIX mscale = XMMatrixScalingFromVector(gameobject->transform->LocalScale);


	XMMATRIX g_World = mscale * mRotation * mTranslate;

	ConstantBuffer cb;
	//std::cout << "\ng_World";
	cb.mWorld = XMMatrixTranspose(g_World);
	//std::cout << "\ng_View";
	//cb.mView = XMMatrixTranspose(Framework::instanse().camera->GetView());
	cb.mView = XMMatrixTranspose(Framework::instanse().camera->g_view);
	//std::cout << "\ng_Projection";
	//cb.mProjection = XMMatrixTranspose(Framework::instanse().camera->GetProjection());
	cb.mProjection = XMMatrixTranspose(Framework::instanse().camera->g_Projection);
	//std::cout << "\nsubresource";
	UINT stride = sizeof(TexturedVertex);
	UINT offset = 0;

	ID3D11DeviceContext *id3d11devicecontext = dxmanager->m_deviceContext;

	id3d11devicecontext->IASetInputLayout(shaderPointers.g_pVertexLayout);


	id3d11devicecontext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

	id3d11devicecontext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	id3d11devicecontext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);


	//std::cout << "\nContext";
	//id3d11devicecontext->VSSetShader(dxmanager->m_VertexShader, NULL, 0);
	id3d11devicecontext->VSSetShader(shaderPointers.m_VertexShader, NULL, 0);
	id3d11devicecontext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	id3d11devicecontext->PSSetShader(shaderPointers.m_PixelShader, NULL, 0);
	id3d11devicecontext->PSSetShaderResources(0, 1, &g_pTextureRV);
	id3d11devicecontext->PSSetSamplers(0, 1, &g_pSamplerLinear);

	id3d11devicecontext->DrawIndexed(NumOfIndexes, 0, 0);
	std::cout << "\nTextMR/";
}
