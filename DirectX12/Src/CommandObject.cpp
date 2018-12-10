#include "CommandObject.h"

cCommandObject::cCommandObject()
{
	m_pAlloc = std::make_shared <cCommandAllocator>();
	m_pList = std::make_shared <cCommandList>(m_pAlloc->GetAllocator(0));
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cCommandObject::GetAllocator(int no)
{
	return m_pAlloc->GetAllocator(no);
}

Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cCommandObject::GetList(int no)
{
	return m_pList->GetListPtr(no);
}
