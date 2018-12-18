#pragma once
#include "Main.h"
#include "PipelineStateObj.h"
#include <unordered_map>
#include <memory>

/// <summary>
/// PSO���Ǘ�����}�l�[�W���[
/// </summary>
class cPSOManager
{
public:
	cPSOManager() = default;
	~cPSOManager() = default;

	static std::shared_ptr<cPipelineStateObj> RequestPSO(std::string);
private:
	// PSO�ɖ��O��t���Ă�����L�[�l�Ƃ��ĕۑ�����
	static std::unordered_map<std::string, std::shared_ptr<cPipelineStateObj>> m_PsoMap;
};
