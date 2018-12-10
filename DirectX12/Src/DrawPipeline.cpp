#include "DrawPipeline.h"
#include "GameTime.h"
#include "Utility.h"

cDrawPipeline::cDrawPipeline()
{
	m_Queue = std::make_unique<cCommandQueue>();
	m_CommandSystem = std::make_unique<cCommandSystem>();
	m_FenceObj = std::make_unique<cFenceObj>();
}

void cDrawPipeline::DrawBigen(int frameIndex)
{
}

void cDrawPipeline::DrawGame(int frameIndex)
{
}

void cDrawPipeline::DrawEnd(int frameIndex)
{
}

void cDrawPipeline::ProcessingCPU(int frameIndex)
{
	// �R�}���h�����܂�؂�̂�҂��Ă���
	if (cGameTime::TortalFrame() > Render::g_LatencyNum)
	{
		m_FenceObj->WaitForPreviousFrame(cGameTime::TortalFrame() - Render::g_LatencyNum);

		CheckHR(m_CommandSystem->GetBeginCommand()->GetAllocator(cGameTime::FrameIndex()).Get()->Reset());
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

}
