#pragma once
#include "Main.h"
#include "Render.h"

class cCommandQueue
{
public:
	cCommandQueue();
	~cCommandQueue() = default;
	inline Microsoft::WRL::ComPtr<ID3D12CommandQueue> GetQueue() { return m_CommandQueue; };
private:
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueue;
};