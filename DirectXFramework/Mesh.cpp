#include "Mesh.h"
#include <iostream>

HRESULT CompileShaderFromFile(LPCSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

HRESULT Mesh::InitShader(std::string ShaderName)
{
	DXManager* dxmanager = Framework::instanse().dxmanager;
	
	auto it = dxmanager->Shaders.find(ShaderName);

	if (it != dxmanager->Shaders.end())
	{
		std::cout << "\nFound Shader Pointer";
		shaderPointers = dxmanager->Shaders[ShaderName];
		return S_OK;
	}

	std::cout << "\nCreating Shader Pointer";

	HRESULT hr;

	
	// Компиляция вершинного шейдера из файла
	ID3DBlob* pVSBlob = NULL; // Вспомогательный объект - просто место в оперативной памяти



	std::cout << "\ncompile vertex shader";
	hr = CompileShaderFromFile(ShaderName.c_str(), "VS", "vs_4_0", &pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Невозможно скомпилировать файл FX. Пожалуйста, запустите данную программу из папки, содержащей файл FX.", "Ошибка", MB_OK);
		return hr;
	}

	// Создание вершинного шейдера
	std::cout << "\ncreate vertex shader";
	hr = dxmanager->m_device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &shaderPointers.m_VertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	};

	/*D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};*/
	//UINT numElements = ARRAYSIZE(layout);

	// Создание шаблона вершин
	std::cout << "\ncreate input layout";
	hr = dxmanager->m_device->CreateInputLayout(layout(), NumberOfElements(), pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &shaderPointers.g_pVertexLayout);

	pVSBlob->Release();
	if (FAILED(hr)) return hr;

	// Подключение шаблона вершин
	dxmanager->m_deviceContext->IASetInputLayout(shaderPointers.g_pVertexLayout);

	// Компиляция пиксельного шейдера из файла
	std::cout << "\ncompile pixel shader";
	ID3DBlob* pPSBlob = NULL;
	hr = CompileShaderFromFile(ShaderName.c_str(), "PS", "ps_4_0", &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Невозможно скомпилировать файл FX. Пожалуйста, запустите данную программу из папки, содержащей файл FX.", "Ошибка", MB_OK);
		return hr;
	}

	std::cout << "\n create pixel shader";
	hr = dxmanager->m_device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &shaderPointers.m_PixelShader);
	pPSBlob->Release();
	if (FAILED(hr)) return hr;

	dxmanager->Shaders.insert(std::pair<std::string,ShaderPointers>(ShaderName,shaderPointers));
	
	std::cout << "\nshader initialized";
	return hr;
	
}
