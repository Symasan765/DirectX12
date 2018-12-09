#include "CommandSystem.h"

cCommandSystem::cCommandSystem()
{
	m_pGameCommand.reset(new cCommandObject[Render::g_LatencyNum]);
	m_pBeginCommand = std::make_unique<cCommandObject>();
	m_pEndCommand = std::make_unique<cCommandObject>();
}
