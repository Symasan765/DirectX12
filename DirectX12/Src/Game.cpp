#include "Game.h"
#include "SystemParameters.h"
#include "Utility.h"

/// <summary>
/// �Q�[���̂����Ƃ����C���ƂȂ�匳�̊֐�
/// </summary>
void cGameSystem::GameUpdate()
{
	
}

cGameSystem::cGameSystem(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ZeroMemory(&m_Msg, sizeof(m_Msg));

	m_hInst = hInst;
	m_hPrevInstance = hPrevInstance;
	m_lpCmdLine = lpCmdLine;
	m_nCmdShow = nCmdShow;

	m_pWindow = new cWindow(hInst, SystemParameters::g_WindowSizeX, SystemParameters::g_WindowSizeY);
	m_pGameTime = new cGameTime;
	m_pDirectX12 = new cDirectX12;
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

			LoopEnd();
		}
	} while (m_Msg.message != WM_QUIT);		//�Ȃɂ�����΂��̂܂܏����𔲂���
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
}

void cGameSystem::LoopBegin()
{
	m_pGameTime->FrameStart();
}

void cGameSystem::LoopEnd()
{
	m_pGameTime->FrameEnd();
}