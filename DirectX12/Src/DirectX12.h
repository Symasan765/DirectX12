#pragma once
#include "Main.h"

/// <summary>
/// DirectX�̊��������舵���N���X
/// </summary>
class cDirectX12
{
public:
	friend class cGameSystem;	// cGameSystem�N���X���ł����쐬�ł��Ȃ��悤�ɂ���
	inline static ID3D12Device* GetDevice() { return m_Device; };
private:
	cDirectX12();
	~cDirectX12();
	static ID3D12Device * m_Device;
};