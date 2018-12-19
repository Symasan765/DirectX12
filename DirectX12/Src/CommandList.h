#pragma once
#include "Main.h"
#include "Render.h"

/// <summary>
/// コマンドリストひとつ分を取り扱うクラス
/// </summary>
class cCommandList
{
public:
	cCommandList(Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAlloc);
	~cCommandList() = default;

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetListPtr(int no) { return m_CommandList[no]; };
private:
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_CommandList[Render::g_LatencyNum];
};