#include "PSOManager.h"

std::shared_ptr<cPipelineStateObj> cPSOManager::RequestPSO(std::string psoName)
{
	auto itr = m_PsoMap.find(psoName);        // "xyz" ‚ªİ’è‚³‚ê‚Ä‚¢‚é‚©H
	if (itr != m_PsoMap.end()) {
		//‚·‚Å‚É“o˜^‚³‚ê‚Ä‚¢‚é
		return itr->second;
	}
	
	// İ’è‚³‚ê‚Ä‚¢‚È‚¯‚ê‚ÎV‚½‚É“o˜^‚µ‚Ä‚»‚ê‚ğ•Ô‚·
	m_PsoMap[psoName] = std::make_shared<cPipelineStateObj>(psoName);
	return m_PsoMap[psoName];
}
