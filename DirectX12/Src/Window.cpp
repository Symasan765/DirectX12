#include "Window.h"
#include "WindProc.h"
#include "SystemParameters.h"
#include "Utility.h"

using namespace SystemParameters;

cWindow::cWindow(HINSTANCE _hInst, int sizeX, int sizeY)
{
	// �E�C���h�E �N���X�̓o�^
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szWndClass;

	if (!RegisterClass(&wc))
		ErrorStop("�E�B���h�E�N���X�̍쐬�Ɏ��s���܂���");
	

	// ���C�� �E�C���h�E�쐬
	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.right = (LONG)sizeX;
	rect.bottom = (LONG)sizeY;
	AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_DLGFRAME, TRUE);

	rect.top = 0.0f;		// ����𖳂����ƃo�[�ʒu����ʊO�֒ǂ����A�t���X�N���[���̂悤�ȏ�Ԃɂł���
	m_hWindow = CreateWindow(g_szWndClass, g_szAppTitle,
		dwStyle,
		rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL, m_hInstance, NULL);

	if (m_hWindow == NULL)
		ErrorStop("�E�B���h�E�̍쐬�Ɏ��s���܂���");

	// �E�C���h�E�\��
	ShowWindow(m_hWindow, SW_SHOWNORMAL);
	UpdateWindow(m_hWindow);
}

cWindow::~cWindow()
{
	// �E�C���h�E �N���X�̓o�^����
	UnregisterClass(g_szWndClass, m_hInstance);
}
