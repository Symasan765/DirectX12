#include "DescriptorBase.h"
#include "Utility.h"
#include "DirectX12.h"
#include <d3dx12.h>

cDescriptorBase::cDescriptorBase(D3D12_DESCRIPTOR_HEAP_TYPE type, D3D12_DESCRIPTOR_HEAP_FLAGS flag, UINT num, UINT NodeMask)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type = type;
	desc.NumDescriptors = num;
	desc.NodeMask = NodeMask;
	desc.Flags = flag;
	CheckHR(cDirectX12::GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(m_DescHeap.ReleaseAndGetAddressOf())));

	// ハンドルのインクリメントサイズを取得しておく
	m_DescriptorHandleIncrementSize = cDirectX12::GetDevice()->GetDescriptorHandleIncrementSize(type);
}

D3D12_CPU_DESCRIPTOR_HANDLE cDescriptorBase::GetHandleCPU(int index)
{
	auto adr = m_DescHeap->GetCPUDescriptorHandleForHeapStart();
	adr.ptr += index * m_DescriptorHandleIncrementSize;
	return adr;
}
