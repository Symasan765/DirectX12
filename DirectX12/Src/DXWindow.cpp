#include "DXWindow.h"
#include "Utility.h"
#include "SystemParameters.h"

Microsoft::WRL::ComPtr<IDXGIFactory4> cDXWindow::m_DxgiFactory;
std::unique_ptr<cWindow> cDXWindow::m_pWindow;
std::unique_ptr<cSwapChain> cDXWindow::m_SwapChain;

cDXWindow::cDXWindow(HINSTANCE _hInst, Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue) {
	// �E�B���h�E���쐬����
	m_pWindow = std::make_unique<cWindow>(_hInst, SystemParameters::g_WindowSizeX, SystemParameters::g_WindowSizeY);


	// DXGI�t�@�N�g���[���쐬����
#if _DEBUG
	CheckHR(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(m_DxgiFactory.ReleaseAndGetAddressOf())));
#else
	CHK(CreateDXGIFactory2(0, IID_PPV_ARGS(mDxgiFactory.ReleaseAndGetAddressOf())));
#endif /* _DEBUG */

	// �X���b�v�`�F�C���̍쐬
	m_SwapChain = std::make_unique<cSwapChain>(queue, m_DxgiFactory, m_pWindow->GetHWND());
}