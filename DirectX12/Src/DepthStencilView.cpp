#include "DepthStencilView.h"
#include "Utility.h"
#include "DirectX12.h"
#include "DescHandleStep.h"

cDepthStencilView::cDepthStencilView(DXGI_FORMAT format, UINT witdh, UINT height,  UINT num, DirectX::XMFLOAT4 color, D3D12_RESOURCE_DIMENSION dimension)
	: cDescriptorBase(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, num)
{
	D3D12_RESOURCE_DESC DepthDesc;
	D3D12_HEAP_PROPERTIES HeapProps;
	D3D12_CLEAR_VALUE ClearValue;
	ZeroMemory(&DepthDesc, sizeof(DepthDesc));
	ZeroMemory(&HeapProps, sizeof(HeapProps));
	ZeroMemory(&ClearValue, sizeof(ClearValue));

	DepthDesc.Dimension = dimension;
	DepthDesc.Width = witdh;
	DepthDesc.Height = height;
	DepthDesc.DepthOrArraySize = 1;
	DepthDesc.MipLevels = 0;
	DepthDesc.Format = format;
	DepthDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	DepthDesc.SampleDesc.Count = 1;
	DepthDesc.SampleDesc.Quality = 0;
	DepthDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	HeapProps.Type = D3D12_HEAP_TYPE_DEFAULT;
	HeapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	HeapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	HeapProps.CreationNodeMask = 0;
	HeapProps.VisibleNodeMask = 0;

	ClearValue.Format = DXGI_FORMAT_D32_FLOAT;
	ClearValue.DepthStencil.Depth = 1.0f;
	ClearValue.DepthStencil.Stencil = 0;

	D3D12_CPU_DESCRIPTOR_HANDLE handle = m_DescHeap->GetCPUDescriptorHandleForHeapStart();
	auto rtvStep = cDirectX12::GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	CheckHR(cDirectX12::GetDevice()->CreateCommittedResource(&HeapProps, D3D12_HEAP_FLAG_NONE, &DepthDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &ClearValue, IID_PPV_ARGS(&m_DsvResource)));

	for (int i = 0; i < Render::g_LatencyNum; i++) {
		D3D12_DEPTH_STENCIL_VIEW_DESC DSVDesc;
		ZeroMemory(&DSVDesc, sizeof(DSVDesc));
		DSVDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		DSVDesc.Format = DXGI_FORMAT_D32_FLOAT;
		DSVDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		DSVDesc.Texture2D.MipSlice = 0;
		DSVDesc.Flags = D3D12_DSV_FLAG_NONE;

		D3D12_CPU_DESCRIPTOR_HANDLE handleDSV;
		handleDSV = m_DescHeap->GetCPUDescriptorHandleForHeapStart();
		handleDSV.ptr += i * cDescHandleStep::GetSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

		cDirectX12::GetDevice()->CreateDepthStencilView(m_DsvResource.Get(), &DSVDesc, handleDSV);
	}
}
