#include "InstVertexBuffer.h"
#include "Utility.h"
#include "GameTime.h"
#include <d3dx12.h>

void cInstVertexBuffer::Create()
{
	for (int i = 0; i < Render::g_LatencyNum; i++) {
		CheckHR(cDirectX12::GetDevice()->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(sizeof(DirectX::XMFLOAT4X4) * Render::g_MaxInstNum),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(mVB[i].ReleaseAndGetAddressOf())));
		cDirectX12::GetDevice()->SetName(L"InstVertexBuffer");
		CheckHR(mVB[i]->Map(0, nullptr, reinterpret_cast<void**>(&vbUploadPtr[i])));
	}
}

void cInstVertexBuffer::SetInstVertexData(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList, DirectX::XMFLOAT4X4 * data, int num, int frameIndex)
{
	UINT size = sizeof(DirectX::XMFLOAT4X4) * num;
	memcpy_s(vbUploadPtr[frameIndex], size, data, size);

	mVBView[frameIndex].BufferLocation = mVB[frameIndex]->GetGPUVirtualAddress();
	mVBView[frameIndex].StrideInBytes = sizeof(DirectX::XMFLOAT4X4);
	mVBView[frameIndex].SizeInBytes = size;

	cmdList->IASetVertexBuffers(1, 1, &mVBView[frameIndex]);
}
