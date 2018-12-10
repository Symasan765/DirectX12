#pragma once
#include "DXWindow.h"
#include "GameTime.h"
#include "DirectX12.h"
#include "DrawPipeline.h"

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
	// 初期化処理
	void SystemInit();
	void AppInit();

	// 解放処理
	void AppUnInit();
	void SystemUnInit();

	// ループの開始時、更新、終了時処理
	void LoopBegin();
	void GameUpdate();
	void CommandRender();
	void LoopEnd();

	cDXWindow* m_pWindow = nullptr;
	cGameTime* m_pGameTime = nullptr;
	cDirectX12* m_pDirectX12 = nullptr;
	cDrawPipeline* m_pDrawPipeline = nullptr;

	// WinMain引数
	HINSTANCE m_hInst;
	HINSTANCE m_hPrevInstance;
	LPSTR m_lpCmdLine;
	int m_nCmdShow;

	MSG m_Msg;	//メッセージ構造体
};