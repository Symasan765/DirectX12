#include "CommandAllocator.h"
#include "Utility.h"
#include "DirectX12.h"

cCommandAllocator::cCommandAllocator()
{
	// コマンドアロケーターの作成
	for (auto& LatencyArray : m_CommandAllocator) {
		CheckHR(cDirectX12::GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(LatencyArray.ReleaseAndGetAddressOf())));
	};
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cCommandAllocator::GetAllocator(int no)
{
#ifdef _DEBUG
	if (no >= Render::g_LatencyNum)
		ErrorStop("渡されたアロケーター番号が不正です");
#endif

	return m_CommandAllocator[no];
}
