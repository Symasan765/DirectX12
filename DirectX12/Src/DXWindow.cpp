#include "DXWindow.h"
#include "Utility.h"
#include "SystemParameters.h"

Microsoft::WRL::ComPtr<IDXGIFactory4> cDXWindow::m_DxgiFactory;
std::unique_ptr<cWindow> cDXWindow::m_pWindow;
std::unique_ptr<cSwapChain> cDXWindow::m_SwapChain;

cDXWindow::cDXWindow(HINSTANCE _hInst, Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue) {
	// ウィンドウを作成する
	m_pWindow = std::make_unique<cWindow>(_hInst, SystemParameters::g_WindowSizeX, SystemParameters::g_WindowSizeY);


	// DXGIファクトリーを作成する
#if _DEBUG
	CheckHR(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(m_DxgiFactory.ReleaseAndGetAddressOf())));
#else
	CHK(CreateDXGIFactory2(0, IID_PPV_ARGS(mDxgiFactory.ReleaseAndGetAddressOf())));
#endif /* _DEBUG */

	// スワップチェインの作成
	m_SwapChain = std::make_unique<cSwapChain>(queue, m_DxgiFactory, m_pWindow->GetHWND());
}