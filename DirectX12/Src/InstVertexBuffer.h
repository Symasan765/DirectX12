#pragma once
#include "DXMath.h"
#include "DirectX12.h"
#include "Render.h"

class cInstVertexBuffer
{
public:
	cInstVertexBuffer() = default;
	~cInstVertexBuffer() = default;

	void Create();
	void SetInstVertexData(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList, DirectX::XMFLOAT4X4* data, int num,int frameIndex);
private:
	Microsoft::WRL::ComPtr<ID3D12Resource> mVB[Render::g_LatencyNum];
	D3D12_VERTEX_BUFFER_VIEW mVBView[Render::g_LatencyNum] = {};
	char* vbUploadPtr[Render::g_LatencyNum] = { nullptr };
};