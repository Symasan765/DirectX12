#pragma once
#include "Window.h"
#include "Main.h"
#include "SwapChain.h"
#include "Render.h"
#include "DepthStencilView.h"
#include "WindowBuuferStruct.h"
#include<memory>

/// <summary>
/// DXGIなど、DirectXプログラムを触る機能を持たせたウィンドウクラス
/// </summary>
class cDXWindow
{
public:
	friend class cGameSystem;	// cGameSystemクラス内でしか作成できないようにする

	inline static Microsoft::WRL::ComPtr<IDXGIFactory4> GetDxgiFactory() { return m_DxgiFactory; };
	static HWND GetHWND() {
		return m_pWindow->GetHWND();
	};

	inline static Microsoft::WRL::ComPtr<ID3D12Resource> GetColorBuffer(int index);
	static WindowBuuferStruct& GetBuuferData() { return m_NowBufferData; };
	static void Present();
private:
	cDXWindow(HINSTANCE _hInst, Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue);
	~cDXWindow() = default;
	void CreateMainWindow(HINSTANCE _hInst, Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue);
	void CreateBuffer();
	void BufferDataUpdate();

	static Microsoft::WRL::ComPtr<IDXGIFactory4> m_DxgiFactory;
	static std::unique_ptr<cWindow> m_pWindow;
	static std::unique_ptr<cSwapChain> m_SwapChain;


	static Microsoft::WRL::ComPtr<ID3D12Resource> m_ColorBuffer[Render::g_LatencyNum];
	static Microsoft::WRL::ComPtr<ID3D12Resource> mDsvResource[Render::g_LatencyNum];
	static std::unique_ptr<cDescriptorBase> m_pRtvHeap;
	static std::unique_ptr<cDepthStencilView> m_pDsvHeap;
	static WindowBuuferStruct m_NowBufferData;
};