#include "ResourceCreateCommand.h"

cResourceCreateCommand::cResourceCreateCommand()
{
	m_Alloc = std::make_unique<cCommandAllocator>();
	m_Queue = std::make_unique<cCommandQueue>();
	m_List = std::make_unique<cCommandList>(m_Alloc->GetAllocator(0));
}

Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cResourceCreateCommand::GetList()
{
	return m_List->GetListPtr(0);
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cResourceCreateCommand::GetAlloc()
{
	return m_Alloc->GetAllocator(0);
}

Microsoft::WRL::ComPtr<ID3D12CommandQueue> cResourceCreateCommand::GetQueue()
{
	return m_Queue->GetQueue();
}
