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

private:
	std::unique_ptr <cCommandAllocator> m_pGameAlloc;
	std::unique_ptr <cCommandList> m_pGameList;
};