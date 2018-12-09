#include "CommandObject.h"

cCommandObject::cCommandObject()
{
	m_pGameAlloc = std::make_unique <cCommandAllocator>();
	m_pGameList = std::make_unique <cCommandList>(m_pGameAlloc->GetAllocator(0));
}
