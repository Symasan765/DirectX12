#pragma once

#include "TimeCheck.h"

/// <summary>
/// ゲーム全体の時間やフレームのカウントを担当する
/// </summary>
class cGameTime
{
public:
	cGameTime();
	~cGameTime() = default;

	void FrameStart();
	void FrameEnd();
private:
	static float m_DeltaTime;
	static long m_TortalFrame;
	static double m_TortalTime;

	static cTimeCheck m_DeltaTimeCheck;
	static cTimeCheck m_TortalTimeCheck;
};