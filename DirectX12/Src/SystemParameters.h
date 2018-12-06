// ----------------------------------------------------------------
// �V�X�e�������̊�{�I�ȃp�����[�^��ێ�����
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// ----------------------------------------------------------------
#pragma once

namespace SystemParameters {
	constexpr int g_WindowSizeX = 1920;
	constexpr int g_WindowSizeY = 1080;

	constexpr char	 g_szWndClass[] = "DirectX12Class";

	// �E�B���h�E�^�C�g���o�^
#if defined(DEBUG) || defined(_DEBUG)
	constexpr CHAR		g_szAppTitle[] = "DirectX12(Debug)";
#else
	constexpr CHAR		g_szAppTitle[] = "DirectX12";
#endif

	// �E�B���h�E�X�^�C��
	constexpr DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_DLGFRAME;
}