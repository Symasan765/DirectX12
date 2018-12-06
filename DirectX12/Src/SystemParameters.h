// ----------------------------------------------------------------
// システム部分の基本的なパラメータを保持する
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// ----------------------------------------------------------------
#pragma once

namespace SystemParameters {
	constexpr int g_WindowSizeX = 1920;
	constexpr int g_WindowSizeY = 1080;

	constexpr char	 g_szWndClass[] = "DirectX12Class";

	// ウィンドウタイトル登録
#if defined(DEBUG) || defined(_DEBUG)
	constexpr CHAR		g_szAppTitle[] = "DirectX12(Debug)";
#else
	constexpr CHAR		g_szAppTitle[] = "DirectX12";
#endif

	// ウィンドウスタイル
	constexpr DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_DLGFRAME;
}