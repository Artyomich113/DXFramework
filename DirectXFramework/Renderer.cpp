#include "Renderer.h"

Renderer::Renderer(DXManager * dxmanager)
{
	std::cout << "base";
	m_device = dxmanager->GetDevice();
	m_deviceContext = dxmanager->GetDeviceContext();
	m_swapChain = dxmanager->GetSwapChain();
	m_renderTargetView = dxmanager->GetRenderTargetView();
}

Renderer::~Renderer()
{

}

Renderer::Renderer()
{

}

