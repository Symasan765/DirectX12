#pragma once
#include "Main.h"
#include "Window.h"
#include<memory>

/// <summary>
/// DXGI�ȂǁADirectX�v���O������G��@�\�����������E�B���h�E�N���X
/// </summary>
class cDXWindow
{
public:
	friend class cGameSystem;	// cGameSystem�N���X���ł����쐬�ł��Ȃ��悤�ɂ���

	inline static Microsoft::WRL::ComPtr<IDXGIFactory2> GetDxgiFactory() { return m_DxgiFactory; };
private:
	cDXWindow(HINSTANCE _hInst);
	~cDXWindow() = default;
	static Microsoft::WRL::ComPtr<IDXGIFactory4> m_DxgiFactory;
	static std::unique_ptr<cWindow> m_pWindow;
};