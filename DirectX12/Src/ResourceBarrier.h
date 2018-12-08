#pragma once
#include "Main.h"

/// <summary>
/// リソース変更のためのバリアを扱うクラス
/// </summary>
class cResourceBarrier
{
public:
	cResourceBarrier() = default;
	~cResourceBarrier() = default;
	void SetState(D3D12_RESOURCE_STATES state0, D3D12_RESOURCE_STATES state1);		// メンバ変数へResourceを追加

	void SwitchState(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList, Microsoft::WRL::ComPtr<ID3D12Resource> res);
private:
	void SwitchingProcess(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList, Microsoft::WRL::ComPtr<ID3D12Resource> res);
	D3D12_RESOURCE_STATES m_State[2] = { D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_COMMON };
};