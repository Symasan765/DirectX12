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

private:
	std::unique_ptr <cCommandObject[]> m_pGameCommand;		// メインゲームで利用するコマンド群
	std::unique_ptr <cCommandObject> m_pBeginCommand;		// 前処理用のコマンド群
	std::unique_ptr <cCommandObject> m_pEndCommand;			// 後処理用のコマンド群
};