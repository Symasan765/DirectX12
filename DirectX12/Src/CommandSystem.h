#pragma once
#include "CommandObject.h"

/// <summary>
/// システムのメイン描画を司るコマンド機能をまとめたクラス
/// </summary>
class cCommandSystem
{
public:
	cCommandSystem();
	~cCommandSystem() = default;

	std::shared_ptr <cCommandObject> GetBeginCommand() { return m_pBeginCommand; };
	std::shared_ptr <cCommandObject> GetEndCommand() { return m_pEndCommand; };

	void AllocReset(int frameIndex);
private:
	std::shared_ptr <cCommandObject[]> m_pGameCommand;		// メインゲームで利用するコマンド群
	std::shared_ptr <cCommandObject> m_pBeginCommand;		// 前処理用のコマンド群
	std::shared_ptr <cCommandObject> m_pEndCommand;			// 後処理用のコマンド群
};