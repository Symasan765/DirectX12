#include "CommandSystem.h"

cCommandSystem::cCommandSystem()
{
	m_pGameCommand.reset(new cCommandObject[Render::g_ThreadNum]);
	m_pBeginCommand = std::make_shared<cCommandObject>();
	m_pEndCommand = std::make_shared<cCommandObject>();
}
