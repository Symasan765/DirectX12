#pragma once
#include <Windows.h>

/// <summary>
/// ウィンドウの作成を行うクラス
/// </summary>
class cWindow
{
public:
	cWindow(HINSTANCE _hInst,int sizeX,int sizeY);
	~cWindow();

private:

	HWND m_hWindow;
	HINSTANCE m_hInstance;
};