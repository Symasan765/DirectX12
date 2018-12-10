#include "DXWindow.h"
#include "Utility.h"
#include "SystemParameters.h"
#include "Render.h"
#include "DirectX12.h"
#include "DXMath.h"
#include "GameTime.h"
#include "DescHandleStep.h"
#include <d3dx12.h>

Microsoft::WRL::ComPtr<IDXGIFactory4> cDXWindow::m_DxgiFactory;
std::unique_ptr<cWindow> cDXWindow::m_pWindow;
std::unique_ptr<cSwapChain> cDXWindow::m_SwapChain;
Microsoft::WRL::ComPtr<ID3D12Resource> cDXWindow::m_ColorBuffer[Render::g_LatencyNum];
Microsoft::WRL::ComPtr<ID3D12Resource> cDXWindow::mDsvResource[Render::g_LatencyNum];
std::unique_ptr<cDescriptorBase> cDXWindow::m_pRtvHeap;
std::unique_ptr<cDepthStencilView> cDXWindow::m_pDsvHeap;
WindowBuuferStruct cDXWindow::m_NowBufferData;

inline Microsoft::WRL::ComPtr<ID3D12Resource> cDXWindow::GetColorBuffer(int index)
{
	return Microsoft::WRL::ComPtr<ID3D12Resource>();
}

void cDXWindow::Present()
{
	m_SwapChain->Present();
}

cDXWindow::cDXWindow(HINSTANCE _hInst, Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue) {
	CreateMainWindow(_hInst, queue);
	CreateBuffer();
}

void cDXWindow::CreateMainWindow(HINSTANCE _hInst, Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue)
{
	// �E�B���h�E���쐬����
	m_pWindow = std::make_unique<cWindow>(_hInst, SystemParameters::g_WindowSizeX, SystemParameters::g_WindowSizeY);


	// DXGI�t�@�N�g���[���쐬����
#if _DEBUG
	CheckHR(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(m_DxgiFactory.ReleaseAndGetAddressOf())));
#else
	CheckHR(CreateDXGIFactory2(0, IID_PPV_ARGS(m_DxgiFactory.ReleaseAndGetAddressOf())));
#endif /* _DEBUG */

	// �X���b�v�`�F�C���̍쐬
	m_SwapChain = std::make_unique<cSwapChain>(queue, m_DxgiFactory, m_pWindow->GetHWND());
}

void cDXWindow::CreateBuffer()
{
	// �X���b�v�`�F�C�����烊�\�[�X���擾����
	for (int i = 0; i < Render::g_LatencyNum; i++)
	{
		CheckHR(m_SwapChain->Get()->GetBuffer(i, IID_PPV_ARGS(m_ColorBuffer[i].ReleaseAndGetAddressOf())));
		m_ColorBuffer[i]->SetName(L"SwapChain_Buffer");
	}

	// �����_�[�^�[�Q�b�g�A�f�v�X�X�e���V���p�̃q�[�v���m��
	m_pRtvHeap = std::make_unique<cDescriptorBase>(D3D12_DESCRIPTOR_HEAP_TYPE_RTV,D3D12_DESCRIPTOR_HEAP_FLAG_NONE, Render::g_LatencyNum);
	m_pDsvHeap = std::make_unique<cDepthStencilView>(DXGI_FORMAT_R32_TYPELESS, SystemParameters::g_WindowSizeX, 
		SystemParameters::g_WindowSizeY, Render::g_LatencyNum, DirectX::XMFLOAT4{ 0.0f,0.0f,0.0f,0.0f });


	// �����_�[�^�[�Q�b�g�r���[�̍쐬
	auto rtvStep = cDirectX12::GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	for (auto i = 0u; i < Render::g_LatencyNum; i++)
	{
		auto d = m_pRtvHeap->GetHeap()->GetCPUDescriptorHandleForHeapStart();
		d.ptr += i * rtvStep;		// �o�b�t�@�i�[�ʒu�A�h���X�����炵�Ă���
		cDirectX12::GetDevice()->CreateRenderTargetView(m_ColorBuffer[i].Get(), nullptr, d);
	}

}

void cDXWindow::BufferDataUpdate()
{
	m_NowBufferData.buffer = m_ColorBuffer[cGameTime::FrameIndex()];
	m_NowBufferData.HeapDsv = m_pDsvHeap->GetHeap();
	m_NowBufferData.HeapRtv = m_pRtvHeap->GetHeap();

	m_NowBufferData.descHandleRtv = m_NowBufferData.HeapRtv->GetCPUDescriptorHandleForHeapStart();
	m_NowBufferData.descHandleRtv.ptr += cGameTime::FrameIndex() * cDescHandleStep::GetSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);		// �擪�A�h���X += (No * �A�h���X�T�C�Y)

	m_NowBufferData.descHandleDsv = m_NowBufferData.HeapDsv->GetCPUDescriptorHandleForHeapStart();
	//m_NowBufferData.descHandleDsv.ptr += cGameTime::FrameIndex() * cDescHandleStep::GetSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);		// �擪�A�h���X += (No * �A�h���X�T�C�Y)
}
