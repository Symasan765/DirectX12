#include "DrawPipeline.h"

cDrawPipeline::cDrawPipeline(Microsoft::WRL::ComPtr<IDXGIFactory2> dxgi, HWND hwnd)
{
	m_Queue = std::make_unique<cCommandQueue>();
	m_SwapChain = std::make_unique<cSwapChain>(m_Queue->GetQueue(),dxgi,hwnd);
}
