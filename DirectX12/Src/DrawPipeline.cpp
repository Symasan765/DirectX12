#include "DrawPipeline.h"
#include "GameTime.h"
#include "DXWindow.h"
#include "Utility.h"
#include "ImGUIManager.h"

cDrawPipeline::cDrawPipeline()
{
	m_Queue = std::make_shared<cCommandQueue>();
	m_CommandSystem = std::make_shared<cCommandSystem>();
	m_FenceObj = std::make_unique<cFenceObj>();
	m_RtvResourceBarrier = std::make_unique<cResourceBarrier>();
	m_RtvResourceBarrier->SetState(D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	m_RenderingFramework = std::make_unique<cRenderingFramework>();
}

cDrawPipeline::~cDrawPipeline()
{
	m_FenceObj->Signal(m_Queue->GetQueue(), cGameTime::TortalFrame());
	Sleep(100);	// TODO ���������Ȃ��ƕ`�揈���I���O��PSO�Ȃǂ̃I�u�W�F�N�g���j������Error���N����
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
	m_RenderingFramework->Draw(m_CommandSystem, frameIndex);
}

void cDrawPipeline::DrawImGUI(int frameIndex)
{
	cImGUIManager::Draw(frameIndex);
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
	m_RenderingFramework->Execute(m_CommandSystem,m_Queue, frameIndex);
}

void cDrawPipeline::ExeImGUI(int frameIndex)
{
	cImGUIManager::Exe(m_Queue->GetQueue(), frameIndex);
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

	DrawImGUI(frameIndex);

	// �㏈��
	DrawEnd(frameIndex);
}

void cDrawPipeline::ProcessingGPU(int frameIndex)
{
	int renderIndex = frameIndex;

	ExeBigen(renderIndex);
	ExeGame(renderIndex);
	ExeImGUI(renderIndex);
	ExeEnd(renderIndex);

	m_FenceObj->Signal(m_Queue->GetQueue(), cGameTime::TortalFrame());
}
