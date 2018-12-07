#pragma once
#include "Main.h"
#include "Window.h"
#include<memory>

/// <summary>
/// DXGIなど、DirectXプログラムを触る機能を持たせたウィンドウクラス
/// </summary>
class cDXWindow
{
public:
	friend class cGameSystem;	// cGameSystemクラス内でしか作成できないようにする

	inline static Microsoft::WRL::ComPtr<IDXGIFactory2> GetDxgiFactory() { return m_DxgiFactory; };
private:
	cDXWindow(HINSTANCE _hInst);
	~cDXWindow() = default;
	static Microsoft::WRL::ComPtr<IDXGIFactory4> m_DxgiFactory;
	static std::unique_ptr<cWindow> m_pWindow;
};