#include "Window.h"
#include "WindProc.h"
#include "SystemParameters.h"
#include "Utility.h"

using namespace SystemParameters;

cWindow::cWindow(HINSTANCE _hInst, int sizeX, int sizeY)
{
	// ウインドウ クラスの登録
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
		ErrorStop("ウィンドウクラスの作成に失敗しました");
	

	// メイン ウインドウ作成
	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.right = (LONG)sizeX;
	rect.bottom = (LONG)sizeY;
	AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_DLGFRAME, TRUE);

	rect.top = 0.0f;		// これを無くすとバー位置を画面外へ追いやり、フルスクリーンのような状態にできる
	m_hWindow = CreateWindow(g_szWndClass, g_szAppTitle,
		dwStyle,
		rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL, m_hInstance, NULL);

	if (m_hWindow == NULL)
		ErrorStop("ウィンドウの作成に失敗しました");

	// ウインドウ表示
	ShowWindow(m_hWindow, SW_SHOWNORMAL);
	UpdateWindow(m_hWindow);
}

cWindow::~cWindow()
{
	// ウインドウ クラスの登録解除
	UnregisterClass(g_szWndClass, m_hInstance);
}
