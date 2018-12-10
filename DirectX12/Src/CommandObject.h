#pragma once
#include "Main.h"
#include "Render.h"
#include "CommandAllocator.h"
#include "CommandList.h"
#include <memory>

class cCommandObject
{
public:
	cCommandObject();
	~cCommandObject() = default;

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> GetAllocator(int no);
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetList(int no);
private:
	std::shared_ptr <cCommandAllocator> m_pAlloc;
	std::shared_ptr <cCommandList> m_pList;
};