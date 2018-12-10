#include "DirectX12.h"
#include "Utility.h"
#include "DescHandleStep.h"

ID3D12Device * cDirectX12::m_Device = nullptr;

cDirectX12::cDirectX12()
{
#if _DEBUG
	// デバッグレイヤーを有効にする
	ID3D12Debug* debug = nullptr;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	if (debug)
	{
		debug->EnableDebugLayer();
		debug->Release();
		debug = nullptr;
	}
#endif /* _DEBUG */

	ID3D12Device* dev;
	CheckHR(D3D12CreateDevice(
		nullptr,
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&dev)));
	m_Device = dev;

	// ヒープサイズをグローバルとして保持しておく
	cDescHandleStep globalDescStep;
	globalDescStep.Init(m_Device);
}

cDirectX12::~cDirectX12()
{
	SAFE_RELEASE(m_Device);
}
