#pragma once
#include "Main.h"
#include "Render.h"

/// <summary>
/// コマンドアロケーターひとつ分を扱うクラス
/// </summary>
class cCommandAllocator
{
public:
	cCommandAllocator();
	~cCommandAllocator() = default;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> GetAllocator(int no);
private:
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_CommandAllocator[Render::g_LatencyNum];
};