#pragma once
#include "Window.h"
#include "Main.h"
#include "SwapChain.h"
#include "Render.h"
#include "DescriptorBase.h"
#include<memory>

/// <summary>
/// DXGIなど、DirectXプログラムを触る機能を持たせたウィンドウクラス
/// </summary>
class cDXWindow
{
public:
	friend class cGameSystem;	// cGameSystemクラス内でしか作成できないようにする

	inline static Microsoft::WRL::ComPtr<IDXGIFactory2> GetDxgiFactory() { return m_DxgiFactory; };
	HWND GetHWND() {
		return m_pWindow->GetHWND();
	};
private:
	cDXWindow(HINSTANCE _hInst, Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue);
	~cDXWindow() = default;
	void CreateMainWindow(HINSTANCE _hInst, Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue);
	void CreateBuffer();

	static Microsoft::WRL::ComPtr<IDXGIFactory4> m_DxgiFactory;
	static std::unique_ptr<cWindow> m_pWindow;
	static std::unique_ptr<cSwapChain> m_SwapChain;


	static Microsoft::WRL::ComPtr<ID3D12Resource> m_ColorBuffer[Render::g_LatencyNum];
	static Microsoft::WRL::ComPtr<ID3D12Resource> mDsvResource[Render::g_LatencyNum];
	static std::unique_ptr<cDescriptorBase> m_pRtvHeap;
	static std::unique_ptr<cDescriptorBase> m_pDsvHeap;
};