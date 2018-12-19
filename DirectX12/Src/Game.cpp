#include "Game.h"
#include "SystemParameters.h"
#include "Utility.h"
#include <thread>

/// <summary>
/// �Q�[���̂����Ƃ����C���ƂȂ�匳�̊֐�
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
	m_ImGUI = new cImGUIManager;
	m_Test = new cTestScene;
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
	// �t���[����x��������̂�1�t���[���ڂ͕`����s�͂����ɍX�V�ƕ`��R�}���h�̔��s�����s���Ă���
	/*LoopBegin();
	GameUpdate();
	LoopEnd();*/

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
			m_ImGUI->NewFrame();						// ImGUI�̃t���[�����X�V����

			ThreadProcess();

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
	SAFE_DELETE(m_pWindow);
	SAFE_DELETE(m_ImGUI);
	SAFE_DELETE(m_Test);
	SAFE_DELETE(m_pDrawPipeline);
	SAFE_DELETE(m_pDirectX12);
}

void cGameSystem::LoopBegin()
{
	m_pGameTime->FrameStart();				// �t���[�������J�E���g������A���Ԃ̌v�����J�n�B
	m_pWindow->BufferDataUpdate();		// �t���[��������J���[�o�b�t�@�̏����X�V����B
}

void cGameSystem::ThreadProcess()
{
	// �V�[���̍X�V�����ƕ`�揈�������ɏ�������
	std::thread gameUpdateThread(&cGameSystem::GameUpdate, this);
	std::thread commandRenderThread(&cGameSystem::CommandRender, this);
	gameUpdateThread.join();
	commandRenderThread.join();
}

void cGameSystem::LoopEnd()
{
	m_pGameTime->FrameEnd();
	cDXWindow::Present();
}