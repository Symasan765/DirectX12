#include "CommandList.h"
#include "Utility.h"
#include "DirectX12.h"

cCommandList::cCommandList(Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAlloc)
{
	for (auto& cmdList : m_CommandList) {
		CheckHR(cDirectX12::GetDevice()->CreateCommandList(
			0,
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			cmdAlloc.Get(),
			nullptr,
			IID_PPV_ARGS(cmdList.ReleaseAndGetAddressOf())));

		cmdList->Close();		// ì¬’¼Œã‚Í‹L˜^ó‘Ô‚É‚È‚Á‚Ä‚¢‚é‚Ì‚Å•Â‚¶‚Ä‚¨‚­
	}
}
