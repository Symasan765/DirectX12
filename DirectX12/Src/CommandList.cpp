#include "CommandList.h"
#include "Utility.h"
#include "DirectX12.h"

cCommandList::cCommandList(Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAlloc)
{
	CheckHR(cDirectX12::GetDevice()->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		cmdAlloc.Get(),
		nullptr,
		IID_PPV_ARGS(m_CommandList.ReleaseAndGetAddressOf())));

	m_CommandList->Close();		// 作成直後は記録状態になっているので閉じておく
}
