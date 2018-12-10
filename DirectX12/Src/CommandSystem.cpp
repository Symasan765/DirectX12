#include "CommandSystem.h"
#include "Utility.h"

cCommandSystem::cCommandSystem()
{
	m_pGameCommand.reset(new cCommandObject[Render::g_ThreadNum]);
	m_pBeginCommand = std::make_shared<cCommandObject>();
	m_pEndCommand = std::make_shared<cCommandObject>();
}

void cCommandSystem::AllocReset(int frameIndex)
{
	CheckHR(m_pBeginCommand->GetAllocator(frameIndex)->Reset());
	CheckHR(m_pEndCommand->GetAllocator(frameIndex)->Reset());
	for (int i = 0; i < Render::g_ThreadNum; i++)
		CheckHR(m_pGameCommand[i].GetAllocator(frameIndex)->Reset());
}
