#include "ImGUIManager.h"
#include "Render.h"
#include "DXWindow.h"
#include "Utility.h"
#include "DirectX12.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx12.h"

Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> cImGUIManager::g_pd3dSrvDescHeap;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cImGUIManager::g_pd3dCommandList;

std::unique_ptr<cDescriptorBase> cImGUIManager::m_Heap;

cImGUIManager::cImGUIManager()
{
	m_Heap = std::make_unique<cDescriptorBase>(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, 1);

	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui_ImplDX12_Init(cDXWindow::GetHWND(), Render::g_LatencyNum, cDirectX12::GetDevice(),
		DXGI_FORMAT_R8G8B8A8_UNORM,
		m_Heap->GetHeap()->GetCPUDescriptorHandleForHeapStart(),
		m_Heap->GetHeap()->GetGPUDescriptorHandleForHeapStart());

	// Setup style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
}

cImGUIManager::~cImGUIManager()
{
	ImGui_ImplDX12_Shutdown();
	ImGui::DestroyContext();
}

void cImGUIManager::NewFrame()
{

}
