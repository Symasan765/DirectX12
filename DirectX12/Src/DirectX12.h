#pragma once
#include "Main.h"

/// <summary>
/// DirectXの基幹部分を取り扱うクラス
/// </summary>
class cDirectX12
{
public:
	friend class cGameSystem;	// cGameSystemクラス内でしか作成できないようにする
	inline static ID3D12Device* GetDevice() { return m_Device; };
private:
	cDirectX12();
	~cDirectX12();
	static ID3D12Device * m_Device;
};