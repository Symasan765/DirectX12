#pragma once
#include "Main.h"
#include "Render.h"

/// <summary>
/// �R�}���h�A���P�[�^�[�ЂƂ��������N���X
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