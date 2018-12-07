#pragma once
#include "Window.h"

/// <summary>
/// メイン関数で作成される全システムの核となるクラス
/// </summary>
class cGameSystem
{
public:
	cGameSystem(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	~cGameSystem();

	void Init();
	void RunLoop();
	void UnInit();
	
private:
	void SystemInit();
	void AppInit();

	void AppUnInit();
	void SystemUnInit();

	cWindow* m_pWindow = nullptr;

	// WinMain引数
	HINSTANCE m_hInst;
	HINSTANCE m_hPrevInstance;
	LPSTR m_lpCmdLine;
	int m_nCmdShow;

	MSG m_Msg;	//メッセージ構造体
};