#pragma once
#include "Main.h"
#include "CommandAllocator.h"
#include "CommandList.h"
#include "CommandQueue.h"
#include <memory>

/// <summary>
/// リソース作成用に使用するアロケーター、リスト、キューをセットにしたクラス
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
	std::shared_ptr<cCommandAllocator> m_Alloc;
	std::shared_ptr<cCommandList> m_List;
	std::shared_ptr<cCommandQueue> m_Queue;
};
