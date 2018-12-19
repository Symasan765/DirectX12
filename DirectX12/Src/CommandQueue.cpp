#include "CommandQueue.h"
#include "Utility.h"
#include "DirectX12.h"

cCommandQueue::cCommandQueue()
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	CheckHR(cDirectX12::GetDevice()->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(m_CommandQueue.ReleaseAndGetAddressOf())));
}


void cCommandQueue::Exe(ID3D12CommandList** pLists, unsigned listNum)
{
	m_CommandQueue->ExecuteCommandLists(listNum, pLists);
}
