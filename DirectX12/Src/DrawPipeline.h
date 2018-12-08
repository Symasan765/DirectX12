#pragma once
#include "CommandQueue.h"

class cDrawPipeline
{
public:
	cDrawPipeline(Microsoft::WRL::ComPtr<IDXGIFactory2> dxgi, HWND hwnd);
	~cDrawPipeline() = default;

private:
	std::unique_ptr<cCommandQueue> m_Queue;
};