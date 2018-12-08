#pragma once
#include "Main.h"

class cSwapChain
{
public:
	cSwapChain(Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue, Microsoft::WRL::ComPtr<IDXGIFactory2> dxgi, HWND hwnd);
	~cSwapChain() = default;
	void Present();
	inline Microsoft::WRL::ComPtr<IDXGISwapChain1> Get() { return m_SwapChain; };
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_SwapChain;
};