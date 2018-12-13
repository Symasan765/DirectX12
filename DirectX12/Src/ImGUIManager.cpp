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
	//m_Heap = std::make_unique<cDescriptorBase>(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, 2);
	//m_CommandObj = std::make_unique<cCommandObject>();

	//// Setup Dear ImGui binding
	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	////io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//ImGui_ImplWin32_Init(cDXWindow::GetHWND());
	//ImGui_ImplDX12_Init(cDirectX12::GetDevice(), Render::g_LatencyNum, DXGI_FORMAT_R8G8B8A8_UNORM, m_Heap->GetHeap()->GetCPUDescriptorHandleForHeapStart(),
	//	m_Heap->GetHeap()->GetGPUDescriptorHandleForHeapStart());

	//// Setup style
	//ImGui::StyleColorsDark();
	////ImGui::StyleColorsClassic();

}

cImGUIManager::~cImGUIManager()
{
	//ImGui_ImplDX12_Shutdown();
	//ImGui_ImplWin32_Shutdown();
	//ImGui::DestroyContext();
}

void cImGUIManager::NewFrame()
{
	//ImGui_ImplDX12_NewFrame();
	//ImGui_ImplWin32_NewFrame();
	//ImGui::NewFrame();
}

void cImGUIManager::Draw(int frameIndex)
{
	//bool show_demo_window = true;
	//bool show_another_window = true;
	//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);

	//{
	//	static float f = 0.0f;
	//	static int counter = 0;

	//	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	//	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	//	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
	//	ImGui::Checkbox("Another Window", &show_another_window);

	//	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
	//	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
	//		counter++;
	//	ImGui::SameLine();
	//	ImGui::Text("counter = %d", counter);

	//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//	ImGui::End();
	//}

	//if (show_another_window)
	//{
	//	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	//	ImGui::Text("Hello from another window!");
	//	if (ImGui::Button("Close Me"))
	//		show_another_window = false;
	//	ImGui::End();
	//}


	//// 各種コマンドを事前に取得しておく。
	//auto commandObj = m_CommandObj.get();
	//auto commandList = commandObj->GetList(frameIndex);
	//auto commandAlloc = commandObj->GetAllocator(frameIndex);
	//CheckHR(commandList->Reset(commandAlloc.Get(), nullptr));

	//commandList->OMSetRenderTargets(1, &cDXWindow::GetBuuferData().HeapRtv->GetCPUDescriptorHandleForHeapStart(), 
	//	false, &cDXWindow::GetBuuferData().HeapDsv->GetCPUDescriptorHandleForHeapStart());
	//auto ptr = m_Heap->GetHeap().Get();
	//commandList->SetDescriptorHeaps(1, &ptr);
	//ImGui::Render();
	//ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(),m_CommandObj->GetList(cGameTime::RenderIndex()).Get());
	//commandList->Close();
}

void cImGUIManager::Exe(Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue, int frameIndex)
{
	/*auto commandObj = m_CommandObj.get();
	auto commandList = commandObj->GetList(frameIndex);
	ID3D12CommandList* list = commandList.Get();
	queue->ExecuteCommandLists(1, &list);*/
}

void cImGUIManager::InvalidateDeviceObjects()
{
	/*ImGui_ImplDX12_InvalidateDeviceObjects();
	ImGui_ImplDX12_CreateDeviceObjects();*/
}

void cImGUIManager::AllocReset(int frameIndex)
{
	//auto commandObj = m_CommandObj.get();
	//auto commandAlloc = commandObj->GetAllocator(frameIndex);
	//commandAlloc->Reset();
}
