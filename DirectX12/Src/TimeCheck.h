#pragma once
#include <Windows.h>

/// <summary>
/// 時間計測を行うクラス
/// </summary>
class cTimeCheck {
public:
	cTimeCheck();
	~cTimeCheck() = default;					//解放処理とくになかった
	void TimerStart();
	void TimerEnd();
	float GetProcessingTime()const;		//かかった処理時間をfloatで返す関数
	float GetAllTime()const;
private:
	LARGE_INTEGER m_Start, m_End;		//処理開始の時間と終了時間を格納する変数
	static LARGE_INTEGER m_Freq;		//単位時間を格納。関数で求めた数値をこの値で割るとsec単位に変換できる。
};