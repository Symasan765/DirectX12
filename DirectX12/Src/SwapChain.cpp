#include "SwapChain.h"
#include "Utility.h"
#include "SwapChain.h"
#include "SystemParameters.h"
#include "Render.h"

cSwapChain::cSwapChain(Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue, Microsoft::WRL::ComPtr<IDXGIFactory4> dxgi, HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC desc = {};
	desc.BufferCount = Render::g_LatencyNum;   // フレームバッファとバックバッファで2枚
	desc.BufferDesc.Width = SystemParameters::g_WindowSizeX;
	desc.BufferDesc.Height = SystemParameters::g_WindowSizeY;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.Windowed = true;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;

	IDXGISwapChain* pSwap;
	CheckHR(dxgi->CreateSwapChain(queue.Get(), &desc, &pSwap));

	CheckHR(pSwap->QueryInterface(IID_PPV_ARGS(&m_SwapChain)));
	pSwap->Release();
	m_SwapChain->SetMaximumFrameLatency(Render::g_LatencyNum);
}

void cSwapChain::Present()
{
	// Present
	CheckHR(m_SwapChain->Present(1, 0));
}
