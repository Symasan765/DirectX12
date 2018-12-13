#include "ImGUIManager.h"
#include "Render.h"
#include "DXWindow.h"
#include "Utility.h"
#include "DirectX12.h"
#include "GameTime.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_win32.h"
#include "ImGUI/imgui_impl_dx12.h"

std::unique_ptr<cDescriptorBase> cImGUIManager::m_Heap;
std::unique_ptr<cCommandObject> cImGUIManager::m_CommandObj;

cImGUIManager::cImGUIManager()
{
	m_Heap = std::make_unique<cDescriptorBase>(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, 2);
	m_CommandObj = std::make_unique<cCommandObject>();

	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui_ImplWin32_Init(cDXWindow::GetHWND());
	ImGui_ImplDX12_Init(cDirectX12::GetDevice(), Render::g_LatencyNum, DXGI_FORMAT_R8G8B8A8_UNORM, m_Heap->GetHeap()->GetCPUDescriptorHandleForHeapStart(),
		m_Heap->GetHeap()->GetGPUDescriptorHandleForHeapStart());

	// Setup style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

}

cImGUIManager::~cImGUIManager()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void cImGUIManager::NewFrame()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void cImGUIManager::Draw(int frameIndex)
{
	// 各種コマンドを事前に取得しておく。
	auto commandObj = m_CommandObj.get();
	auto commandList = commandObj->GetList(frameIndex);
	auto commandAlloc = commandObj->GetAllocator(frameIndex);
	commandAlloc->Reset();
	CheckHR(commandList->Reset(commandAlloc.Get(), nullptr));

	auto d3dBuffer = cDXWindow::GetBuuferData().buffer;
	commandList->OMSetRenderTargets(1, &cDXWindow::GetBuuferData().HeapRtv->GetCPUDescriptorHandleForHeapStart(), FALSE, NULL);
	auto ptr = m_Heap->GetHeap().Get();
	//auto ptr = m_Heap->GetHeap();
	commandList->SetDescriptorHeaps(1, &ptr);
	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(),m_CommandObj->GetList(cGameTime::RenderIndex()).Get());
	commandList->Close();
}

void cImGUIManager::Exe(Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue, int frameIndex)
{
	auto commandObj = m_CommandObj.get();
	auto commandList = commandObj->GetList(frameIndex);
	ID3D12CommandList* list = commandList.Get();
	queue->ExecuteCommandLists(1, &list);
}

void cImGUIManager::InvalidateDeviceObjects()
{
	ImGui_ImplDX12_InvalidateDeviceObjects();
	ImGui_ImplDX12_CreateDeviceObjects();
}
