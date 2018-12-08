#pragma once
#include "CommandQueue.h"
#include "SwapChain.h"

class cDrawPipeline
{
public:
	cDrawPipeline(Microsoft::WRL::ComPtr<IDXGIFactory2> dxgi, HWND hwnd);
	~cDrawPipeline() = default;

private:
	std::unique_ptr<cCommandQueue> m_Queue;
	std::unique_ptr<cSwapChain> m_SwapChain;
};