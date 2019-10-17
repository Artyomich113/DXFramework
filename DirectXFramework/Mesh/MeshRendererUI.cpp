#include "MeshRendererUI.h"

MeshRendererUI::MeshRendererUI(const MeshRendererUI &ob)
{
	NumOfIndexes = ob.NumOfIndexes;
	NumOfVerteces = ob.NumOfVerteces;

	g_pVertexBuffer = ob.g_pVertexBuffer;
	g_pIndexBuffer = ob.g_pIndexBuffer;
	g_pConstantBuffer = ob.g_pConstantBuffer;


	shaderPointers = ob.shaderPointers;
	dxmanager = Framework::instanse().GetDXManager();
}

HRESULT MeshRendererUI::InitMesh()
{
	std::cout << "\ninit mesh";
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC bd;	// ���������, ����������� ����������� �����
	//std::cout << "\nzero memory";
	ZeroMemory(&bd, sizeof(bd));				// ������� ��
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * NumOfVerteces;	// ������ ������
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ��� ������ - ����� ������
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;	// ���������, ���������� ������ ������
	//std::cout << "\nzero memory";
	ZeroMemory(&InitData, sizeof(InitData));	// ������� ��
	InitData.pSysMem = Vertices;				// ��������� �� ���� 8 ������
	// ����� ������ g_pd3dDevice ������� ������ ������ ������
	std::cout << "\n   createbuffer";
	hr = dxmanager->m_device->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
	std::cout << "\n   buffer created";
	if (FAILED(hr))
	{
		std::cout << "\n  failed create vertices buffer " << NumOfVerteces << " vecteces";
		return hr;
	}

	bd.Usage = D3D11_USAGE_DEFAULT;		// ���������, ����������� ����������� �����
	bd.ByteWidth = sizeof(WORD) * NumOfIndexes;	// ��� 6 ������������� ���������� 18 ������
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER; // ��� - ����� ��������
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = Indices;				// ��������� �� ��� ������ ��������
	// ����� ������ g_pd3dDevice ������� ������ ������ ��������
	std::cout << "\n    creating indeces buffer";
	hr = dxmanager->m_device->CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
	if (FAILED(hr))
	{
		std::cout << "\n   failed create indices buffer";
		return hr;
	}


	dxmanager->m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �������� ������������ ������
	bd.Usage = D3D11_USAGE_DEFAULT;
	//std::cout << "bytewidth" << sizeof(ConstantBufferUI);
	bd.ByteWidth = sizeof(ConstantBufferUI);		// ������ ������ = ������� ���������
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// ��� - ����������� �����
	bd.CPUAccessFlags = 0;
	std::cout << "\n creating constant buffer";
	hr = dxmanager->m_device->CreateBuffer(&bd, NULL, &g_pConstantBuffer);
	if (FAILED(hr))
	{
		std::cout << "\nfailed create costant buffer";
		return hr;
	}
	return hr;
}

MeshRendererUI::MeshRendererUI(SimpleVertex *vertices, WORD* indices, int NumberOfIndexes, int NumberOfVerteces)
{
	Vertices = vertices;
	Indices = indices;
	this->NumOfIndexes = NumberOfIndexes;
	this->NumOfVerteces = NumberOfVerteces;
	dxmanager = Framework::instanse().GetDXManager();
}

D3D11_INPUT_ELEMENT_DESC * MeshRendererUI::layout()
{
	D3D11_INPUT_ELEMENT_DESC *layout = new D3D11_INPUT_ELEMENT_DESC[2];
	layout[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	layout[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 };

	std::cout << "\nReturning Layout " << layout;
	return layout;
}

UINT MeshRendererUI::NumberOfElements()
{
	return (UINT)2;
}

MeshRendererUI::~MeshRendererUI()
{
	if (g_pConstantBuffer)g_pConstantBuffer->Release();
	if (g_pIndexBuffer)g_pIndexBuffer->Release();
	if (g_pVertexBuffer)g_pVertexBuffer->Release();
	delete Vertices;
	delete Indices;
}

void MeshRendererUI::process()
{
	//std::cout <<"\nMR";
	XMMATRIX mRotation = XMMatrixRotationQuaternion(gameobject->transform->Rotation);
	//XMMATRIX mRotation = XMMatrixRotationRollPitchYawFromVector(gameobject->transform->Rotation);

	XMMATRIX mTranslate = XMMatrixTranslationFromVector(gameobject->transform->Position);

	XMMATRIX mscale = XMMatrixScalingFromVector(gameobject->transform->LocalScale);


	XMMATRIX g_World = mscale * mRotation * mTranslate;

	ConstantBufferUI cb;
	//std::cout << "\ng_World";
	cb.mWorld = XMMatrixTranspose(g_World);
	//std::cout << "\ng_View";
	//cb.mView = XMMatrixTranspose(Framework::instanse().camera->GetView());
	//cb.mView = XMMatrixLookToLH(XMVectorSet(0.0f,0.0f,0.0f,0.0f), XMVectorSet(0.0f,0.0f,1.0f,0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

	//XMMatrixTranspose(Framework::instanse().camera->g_view);
	//std::cout << "\ng_Projection";
	//cb.mProjection = XMMatrixTranspose(Framework::instanse().camera->GetProjection());
	//cb.mProjection = XMMatrixTranspose(Framework::instanse().camera->g_Projection);
	cb.mProjection = XMMatrixTranspose(XMMatrixOrthographicOffCenterLH(-2.0f,2.0f,-2.0f,2.0f,0.01f,100.0f));
	//std::cout << "\nsubresource";
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;

	ID3D11DeviceContext *id3d11devicecontext = dxmanager->m_deviceContext;

	//id3d11devicecontext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);
	id3d11devicecontext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

	id3d11devicecontext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	id3d11devicecontext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);


	//std::cout << "\nContext";
	//id3d11devicecontext->VSSetShader(dxmanager->m_VertexShader, NULL, 0);
	id3d11devicecontext->VSSetShader(shaderPointers.m_VertexShader, NULL, 0);
	id3d11devicecontext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	id3d11devicecontext->PSSetShader(shaderPointers.m_PixelShader, NULL, 0);
	id3d11devicecontext->DrawIndexed(NumOfIndexes, 0, 0);
}
