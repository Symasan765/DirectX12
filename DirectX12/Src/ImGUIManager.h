#pragma once
#include "Main.h"
#include "DescriptorBase.h"
#include <memory>

class cImGUIManager {
public:
	friend class cGameSystem;
	cImGUIManager();
	~cImGUIManager();

	static void DrawCommand(Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator, Microsoft::WRL::ComPtr<ID3D12Resource> RenderTargetResource, D3D12_CPU_DESCRIPTOR_HANDLE& descHandleRtv);
	inline static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetCommandList() { return g_pd3dCommandList; };
private:
	// •s—v =====
	void Create();
	void CreateDescriptorHeap();
	void CreateCommandList();
	void Destroy();

	static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> g_pd3dSrvDescHeap;
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> g_pd3dCommandList;
	//========
	void NewFrame();

	static std::unique_ptr<cDescriptorBase> m_Heap;
};