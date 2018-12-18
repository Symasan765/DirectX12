#include "PSOManager.h"

std::shared_ptr<cPipelineStateObj> cPSOManager::RequestPSO(std::string psoName)
{
	auto itr = m_PsoMap.find(psoName);        // "xyz" ���ݒ肳��Ă��邩�H
	if (itr != m_PsoMap.end()) {
		//���łɓo�^����Ă���
		return itr->second;
	}
	
	// �ݒ肳��Ă��Ȃ���ΐV���ɓo�^���Ă����Ԃ�
	m_PsoMap[psoName] = std::make_shared<cPipelineStateObj>(psoName);
	return m_PsoMap[psoName];
}
