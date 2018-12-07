#include "CommandAllocator.h"
#include "Utility.h"
#include "DirectX12.h"

cCommandAllocator::cCommandAllocator()
{
	// �R�}���h�A���P�[�^�[�̍쐬
	for (auto& LatencyArray : m_CommandAllocator) {
		CheckHR(cDirectX12::GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(LatencyArray.ReleaseAndGetAddressOf())));
	};
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cCommandAllocator::GetAllocator(int no)
{
#ifdef _DEBUG
	if (no >= Render::g_LatencyNum)
		ErrorStop("�n���ꂽ�A���P�[�^�[�ԍ����s���ł�");
#endif

	return m_CommandAllocator[no];
}
