#pragma once
#include "Main.h"

/// <summary>
/// ��ʂփX�v���C�g��`�悷��N���X
/// </summary>
class cScreenQuad
{
public:
	cScreenQuad();
	~cScreenQuad() = default;
	void Draw(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList,int frameIndex);
private:
	void Init();

	static Microsoft::WRL::ComPtr<ID3D12Resource> m_VB;
	static D3D12_VERTEX_BUFFER_VIEW m_VbView;
	static bool m_InitFlag;
};