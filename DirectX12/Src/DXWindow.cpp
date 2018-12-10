#include "DXWindow.h"
#include "Utility.h"
#include "SystemParameters.h"
#include "Render.h"
#include "DirectX12.h"
#include "DXMath.h"
#include <d3dx12.h>

Microsoft::WRL::ComPtr<IDXGIFactory4> cDXWindow::m_DxgiFactory;
std::unique_ptr<cWindow> cDXWindow::m_pWindow;
std::unique_ptr<cSwapChain> cDXWindow::m_SwapChain;
Microsoft::WRL::ComPtr<ID3D12Resource> cDXWindow::m_ColorBuffer[Render::g_LatencyNum];
Microsoft::WRL::ComPtr<ID3D12Resource> cDXWindow::mDsvResource[Render::g_LatencyNum];
std::unique_ptr<cDescriptorBase> cDXWindow::m_pRtvHeap;
std::unique_ptr<cDepthStencilView> cDXWindow::m_pDsvHeap;

cDXWindow::cDXWindow(HINSTANCE _hInst, Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue) {
	CreateMainWindow(_hInst, queue);
	CreateBuffer();
}

void cDXWindow::CreateMainWindow(HINSTANCE _hInst, Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue)
{
	// ウィンドウを作成する
	m_pWindow = std::make_unique<cWindow>(_hInst, SystemParameters::g_WindowSizeX, SystemParameters::g_WindowSizeY);


	// DXGIファクトリーを作成する
#if _DEBUG
	CheckHR(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(m_DxgiFactory.ReleaseAndGetAddressOf())));
#else
	CheckHR(CreateDXGIFactory2(0, IID_PPV_ARGS(m_DxgiFactory.ReleaseAndGetAddressOf())));
#endif /* _DEBUG */

	// スワップチェインの作成
	m_SwapChain = std::make_unique<cSwapChain>(queue, m_DxgiFactory, m_pWindow->GetHWND());
}

void cDXWindow::CreateBuffer()
{
	// スワップチェインからリソースを取得する
	for (int i = 0; i < Render::g_LatencyNum; i++)
	{
		CheckHR(m_SwapChain->Get()->GetBuffer(i, IID_PPV_ARGS(m_ColorBuffer[i].ReleaseAndGetAddressOf())));
		m_ColorBuffer[i]->SetName(L"SwapChain_Buffer");
	}

	// レンダーターゲット、デプスステンシル用のヒープを確保
	m_pRtvHeap = std::make_unique<cDescriptorBase>(D3D12_DESCRIPTOR_HEAP_TYPE_RTV,D3D12_DESCRIPTOR_HEAP_FLAG_NONE, Render::g_LatencyNum);
	m_pDsvHeap = std::make_unique<cDepthStencilView>(DXGI_FORMAT_R32_TYPELESS, SystemParameters::g_WindowSizeX, 
		SystemParameters::g_WindowSizeY, Render::g_LatencyNum, DirectX::XMFLOAT4{ 0.0f,0.0f,0.0f,0.0f });


	// レンダーターゲットビューの作成
	auto rtvStep = cDirectX12::GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	for (auto i = 0u; i < Render::g_LatencyNum; i++)
	{
		auto d = m_pRtvHeap->GetHeap()->GetCPUDescriptorHandleForHeapStart();
		d.ptr += i * rtvStep;		// バッファ格納位置アドレスをずらしている
		cDirectX12::GetDevice()->CreateRenderTargetView(m_ColorBuffer[i].Get(), nullptr, d);
	}

}
