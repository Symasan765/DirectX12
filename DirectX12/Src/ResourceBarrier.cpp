#include "ResourceBarrier.h"

void cResourceBarrier::SetState(D3D12_RESOURCE_STATES state0, D3D12_RESOURCE_STATES state1)
{
	m_State[0] = state0;
	m_State[1] = state1;
}

void cResourceBarrier::SwitchState(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList, Microsoft::WRL::ComPtr<ID3D12Resource> res)
{
	// é¿çsÇµÇΩÇÁì¸ÇÍë÷Ç¶ÇƒÇ®Ç≠
	SwitchingProcess(cmdList, res);

	auto val = m_State[0];
	m_State[0] = m_State[1];
	m_State[1] = val;
}

void cResourceBarrier::SwitchingProcess(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList, Microsoft::WRL::ComPtr<ID3D12Resource> res)
{
	D3D12_RESOURCE_BARRIER desc = {};
	desc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	desc.Transition.pResource = res.Get();
	desc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	desc.Transition.StateBefore = m_State[0];
	desc.Transition.StateAfter = m_State[1];
	desc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	cmdList->ResourceBarrier(1, &desc);
}