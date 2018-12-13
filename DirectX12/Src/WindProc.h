#pragma once
#include <Windows.h>
#include "ImGUIManager.h"

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
		cImGUIManager::InvalidateDeviceObjects();
		return 0;
	case WM_DESTROY: {
		// ウインドウを閉じる
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN: {
		// キー入力の処理
		switch (wParam)
		{
		case VK_ESCAPE:	// [ESC]キーでウインドウを閉じる
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
	}
	}
	// デフォルト処理
	return DefWindowProc(hWnd, msg, wParam, lParam);
}