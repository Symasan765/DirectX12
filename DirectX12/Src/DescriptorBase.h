#pragma once
#include "Main.h"

class cDescriptorBase
{
public:
	cDescriptorBase(D3D12_DESCRIPTOR_HEAP_TYPE type, D3D12_DESCRIPTOR_HEAP_FLAGS flag, UINT num, UINT NodeMask = 0);
	virtual ~cDescriptorBase() = default;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetHeap() { return m_DescHeap; };


	D3D12_CPU_DESCRIPTOR_HANDLE GetHandleCPU(int index);
protected:
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_DescHeap = nullptr;
	UINT m_DescriptorHandleIncrementSize = 0;
};