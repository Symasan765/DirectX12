#include "PSOManager.h"

std::shared_ptr<cPipelineStateObj> cPSOManager::RequestPSO(std::string psoName)
{
	auto itr = m_PsoMap.find(psoName);        // "xyz" が設定されているか？
	if (itr != m_PsoMap.end()) {
		//すでに登録されている
		return itr->second;
	}
	
	// 設定されていなければ新たに登録してそれを返す
	m_PsoMap[psoName] = std::make_shared<cPipelineStateObj>(psoName);
	return m_PsoMap[psoName];
}
