#include "SwapChain.h"
#include "Utility.h"
#include "SwapChain.h"
#include "SystemParameters.h"
#include "Render.h"

cSwapChain::cSwapChain(Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue, Microsoft::WRL::ComPtr<IDXGIFactory2> dxgi, HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC1 scDesc = {};
	scDesc.Width = SystemParameters::g_WindowSizeX;
	scDesc.Height = SystemParameters::g_WindowSizeY;
	scDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.SampleDesc.Count = 1;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.BufferCount = Render::g_LatencyNum;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	CheckHR(dxgi->CreateSwapChainForHwnd(queue.Get(), hwnd, &scDesc, nullptr, nullptr, m_SwapChain.ReleaseAndGetAddressOf()));
}

void cSwapChain::Present()
{
	// Present
	CheckHR(m_SwapChain->Present(1, 0));
}
