#pragma once
#include "Main.h"

/// <summary>
/// コマンドリストひとつ分を取り扱うクラス
/// </summary>
class cCommandList
{
public:
	cCommandList(Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAlloc);
	~cCommandList() = default;

	inline Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetListPtr() { return m_CommandList; };
private:
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_CommandList;
};