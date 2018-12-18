#pragma once
#include "Main.h"
#include "PipelineStateObj.h"
#include <unordered_map>
#include <memory>

/// <summary>
/// PSOを管理するマネージャー
/// </summary>
class cPSOManager
{
public:
	cPSOManager() = default;
	~cPSOManager() = default;

	static std::shared_ptr<cPipelineStateObj> RequestPSO(std::string);
private:
	// PSOに名前を付けてそれをキー値として保存する
	static std::unordered_map<std::string, std::shared_ptr<cPipelineStateObj>> m_PsoMap;
};
