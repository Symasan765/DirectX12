#pragma once
#include <Windows.h>

/// <summary>
/// �E�B���h�E�̍쐬���s���N���X
/// </summary>
class cWindow
{
public:
	cWindow(HINSTANCE _hInst,int sizeX,int sizeY);
	~cWindow();
	HWND GetHWND();
	HINSTANCE GetHINSTANCE();
private:

	HWND m_hWindow;
	HINSTANCE m_hInstance;
};