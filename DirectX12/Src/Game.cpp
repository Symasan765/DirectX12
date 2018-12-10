#include "Game.h"
#include "SystemParameters.h"
#include "Utility.h"

/// <summary>
/// ゲームのもっともメインとなる大元の関数
/// </summary>
void cGameSystem::GameUpdate()
{
	
}

void cGameSystem::CommandRender()
{
	m_pDrawPipeline->ProcessingCPU(cGameTime::RenderIndex());
	m_pDrawPipeline->ProcessingGPU(cGameTime::RenderIndex());
}

cGameSystem::cGameSystem(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ZeroMemory(&m_Msg, sizeof(m_Msg));

	m_hInst = hInst;
	m_hPrevInstance = hPrevInstance;
	m_lpCmdLine = lpCmdLine;
	m_nCmdShow = nCmdShow;

	m_pDirectX12 = new cDirectX12;
	m_pDrawPipeline = new cDrawPipeline();
	m_pWindow = new cDXWindow(hInst, m_pDrawPipeline->m_Queue->GetQueue());
	m_pGameTime = new cGameTime;
}

cGameSystem::~cGameSystem()
{
	
}

void cGameSystem::SystemInit()
{
}

void cGameSystem::AppInit()
{
}

void cGameSystem::Init()
{
	SystemInit();
	AppInit();
}

void cGameSystem::RunLoop()
{
	// フレームを遅延させるので1フレーム目は描画実行はせずに更新と描画コマンドの発行だけ行っておく
	LoopBegin();
	GameUpdate();
	LoopEnd();

	do
	{
		if (PeekMessage(&m_Msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_Msg);
			DispatchMessage(&m_Msg);
		}
		else
		{
			LoopBegin();

			GameUpdate();
			CommandRender();

			LoopEnd();
		}
	} while (m_Msg.message != WM_QUIT);		//なにかあればそのまま処理を抜ける
}

void cGameSystem::UnInit()
{
	SystemUnInit();
	AppUnInit();
}

void cGameSystem::AppUnInit()
{
}

void cGameSystem::SystemUnInit()
{
	SAFE_DELETE(m_pGameTime);
	SAFE_DELETE(m_pDirectX12);
	SAFE_DELETE(m_pWindow);
	SAFE_DELETE(m_pDrawPipeline);
}

void cGameSystem::LoopBegin()
{
	m_pGameTime->FrameStart();				// フレーム数をカウントしたり、時間の計測を開始。
	m_pWindow->BufferDataUpdate();		// フレーム数からカラーバッファの情報を更新する。
}

void cGameSystem::LoopEnd()
{
	m_pGameTime->FrameEnd();
	cDXWindow::Present();
}