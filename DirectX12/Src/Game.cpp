#include "Game.h"
#include "SystemParameters.h"

cGameSystem::cGameSystem(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ZeroMemory(&m_Msg, sizeof(m_Msg));

	m_hInst = hInst;
	m_hPrevInstance = hPrevInstance;
	m_lpCmdLine = lpCmdLine;
	m_nCmdShow = nCmdShow;

	m_pWindow = new cWindow(hInst, SystemParameters::g_WindowSizeX, SystemParameters::g_WindowSizeY);
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
			
		}
	} while (m_Msg.message != WM_QUIT);		//Ç»Ç…Ç©Ç†ÇÍÇŒÇªÇÃÇ‹Ç‹èàóùÇî≤ÇØÇÈ
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
}
