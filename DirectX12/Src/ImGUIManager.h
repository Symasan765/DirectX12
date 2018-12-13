#pragma once
#include "Main.h"
#include "DescriptorBase.h"
#include <memory>
#include "CommandObject.h"

class cImGUIManager {
public:
	friend class cGameSystem;
	cImGUIManager();
	~cImGUIManager();

	static void DrawCommand(Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator, Microsoft::WRL::ComPtr<ID3D12Resource> RenderTargetResource, D3D12_CPU_DESCRIPTOR_HANDLE& descHandleRtv);
	static void Draw(int frameIndex);
	static void Exe(Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue, int frameIndex);
	static void InvalidateDeviceObjects();		// ウィンドウプロシージャからの呼び出しだけ
private:
	// 不要 =====
	void Create();
	void CreateDescriptorHeap();
	void CreateCommandList();
	void Destroy();
	//========
	void NewFrame();

	static std::unique_ptr<cDescriptorBase> m_Heap;
	static std::unique_ptr<cCommandObject> m_CommandObj;
};