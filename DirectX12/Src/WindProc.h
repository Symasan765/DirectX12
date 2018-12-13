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
		// �E�C���h�E�����
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN: {
		// �L�[���͂̏���
		switch (wParam)
		{
		case VK_ESCAPE:	// [ESC]�L�[�ŃE�C���h�E�����
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
	}
	}
	// �f�t�H���g����
	return DefWindowProc(hWnd, msg, wParam, lParam);
}