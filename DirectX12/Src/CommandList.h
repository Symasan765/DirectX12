#pragma once
#include "Main.h"
#include "Render.h"

/// <summary>
/// �R�}���h���X�g�ЂƂ�����舵���N���X
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