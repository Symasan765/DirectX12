#pragma once
#include "CommandSystem.h"
#include "CommandQueue.h"
#include "PSOManager.h"
// ������
#include "ConstantBuffer.h"
#include "DXMath.h"

struct CBuffer {
	DirectX::XMFLOAT4X4 worldViewProjMatrix;
	DirectX::XMFLOAT4X4 worldMatrix;
};

/// <summary>
/// �Q�[���I�u�W�F�N�g�̕`���S������`��̍ł��v�ƂȂ�N���X
/// </summary>
class cRenderingFramework
{
public:
	cRenderingFramework();
	~cRenderingFramework() = default;

	void Draw(std::shared_ptr<cCommandSystem> m_CommandSystem,int frameIndex);		// �R�}���h���s
	void Execute(std::shared_ptr<cCommandSystem> m_CommandSystem, std::shared_ptr<cCommandQueue> queue, int frameIndex);					// �R�}���h���s
private:
	void OpaquePass(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList, Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAlloc,int frameIndex);	// �s�����p�X
	void CreatePSO();		// ���̒��Ńv���O�������ŕK�v��PSO���쐬����
	std::unique_ptr<cPSOManager> m_PsoManager;
	cConstBuf<CBuffer> m_ConstBuf;
};