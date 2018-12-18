#pragma once
#include "Main.h"
#include "CommandAllocator.h"
#include "CommandList.h"
#include "CommandQueue.h"
#include <memory>

/// <summary>
/// ���\�[�X�쐬�p�Ɏg�p����A���P�[�^�[�A���X�g�A�L���[���Z�b�g�ɂ����N���X
/// </summary>
class cResourceCreateCommand
{
public:
	cResourceCreateCommand();
	~cResourceCreateCommand() = default;
	
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetList();
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> GetAlloc();
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> GetQueue();
private:
	std::unique_ptr<cCommandAllocator> m_Alloc;
	std::unique_ptr<cCommandList> m_List;
	std::unique_ptr<cCommandQueue> m_Queue;
};
