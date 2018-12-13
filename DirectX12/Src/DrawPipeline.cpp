#include "DrawPipeline.h"
#include "GameTime.h"
#include "DXWindow.h"
#include "Utility.h"
#include "ImGUIManager.h"

cDrawPipeline::cDrawPipeline()
{
	m_Queue = std::make_unique<cCommandQueue>();
	m_CommandSystem = std::make_unique<cCommandSystem>();
	m_FenceObj = std::make_unique<cFenceObj>();
	m_RtvResourceBarrier = std::make_unique<cResourceBarrier>();
	m_RtvResourceBarrier->SetState(D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
}

void cDrawPipeline::DrawBigen(int frameIndex)
{
	// �e��R�}���h�����O�Ɏ擾���Ă����B
	auto commandObj = m_CommandSystem->GetBeginCommand();
	auto commandList = commandObj->GetList(frameIndex);
	auto commandAlloc = commandObj->GetAllocator(frameIndex);
	CheckHR(commandList->Reset(commandAlloc.Get(), nullptr));

	auto d3dBuffer = cDXWindow::GetBuuferData().buffer;
	m_RtvResourceBarrier->SwitchState(commandList, d3dBuffer);

	// �f�v�X�X�e���V��������������
	commandList->ClearDepthStencilView(cDXWindow::GetBuuferData().descHandleDsv, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	// �����_�[�^�[�Q�b�g���N���A
	{
		const float ClearColor[4] = { 0.1f, 0.2f, 0.6f, 1.0f };
		commandList->ClearRenderTargetView(cDXWindow::GetBuuferData().descHandleRtv, ClearColor, 0, nullptr);
	}

	// �`��O�����̏I��
	CheckHR(commandList->Close());
}

void cDrawPipeline::DrawGame(int frameIndex)
{
	cImGUIManager::Draw(cGameTime::RenderIndex());
}

void cDrawPipeline::DrawEnd(int frameIndex)
{
	auto commandObj = m_CommandSystem->GetEndCommand();
	auto commandList = commandObj->GetList(frameIndex);
	auto commandAlloc = commandObj->GetAllocator(frameIndex);


	CheckHR(commandList->Reset(commandAlloc.Get(), nullptr));

	// �o���A�����Ƃɖ߂�
	auto d3dBuffer = cDXWindow::GetBuuferData().buffer;
	m_RtvResourceBarrier->SwitchState(commandList, d3dBuffer);

	CheckHR(commandList->Close());
}

void cDrawPipeline::ExeBigen(int frameIndex)
{
	// �e��R�}���h�����O�Ɏ擾���Ă����B
	auto commandObj = m_CommandSystem->GetBeginCommand();
	auto commandList = commandObj->GetList(frameIndex);
	auto commandAlloc = commandObj->GetAllocator(frameIndex);

	ID3D12CommandList* list = commandList.Get();

	m_Queue->GetQueue()->ExecuteCommandLists(1, &list);
}

void cDrawPipeline::ExeGame(int frameIndex)
{
	cImGUIManager::Exe(m_Queue->GetQueue(), cGameTime::RenderIndex());
}

void cDrawPipeline::ExeEnd(int frameIndex)
{
	// �e��R�}���h�����O�Ɏ擾���Ă����B
	auto commandObj = m_CommandSystem->GetEndCommand();
	auto commandList = commandObj->GetList(frameIndex);
	auto commandAlloc = commandObj->GetAllocator(frameIndex);

	ID3D12CommandList* list = commandList.Get();

	m_Queue->GetQueue()->ExecuteCommandLists(1, &list);
}

void cDrawPipeline::ProcessingCPU(int frameIndex)
{
	// �R�}���h�����܂�؂�̂�҂��Ă���
	if (cGameTime::TortalFrame() > Render::g_LatencyNum - 1)
	{
		m_FenceObj->WaitForPreviousFrame(cGameTime::TortalFrame() - Render::g_LatencyNum);

		m_CommandSystem->AllocReset(frameIndex);
		cImGUIManager::AllocReset(frameIndex);
	}


	// �O����
	DrawBigen(frameIndex);

	// �Q�[������
	DrawGame(frameIndex);

	// �㏈��
	DrawEnd(frameIndex);
}

void cDrawPipeline::ProcessingGPU(int frameIndex)
{
	int renderIndex = frameIndex;

	ExeBigen(renderIndex);
	ExeGame(renderIndex);
	ExeEnd(renderIndex);

	m_FenceObj->Signal(m_Queue->GetQueue(), cGameTime::TortalFrame());
}
