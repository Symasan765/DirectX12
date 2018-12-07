#include "GameTime.h"

float cGameTime::m_DeltaTime = 0;
long cGameTime::m_TortalFrame = 0;
double cGameTime::m_TortalTime = 0;
cTimeCheck cGameTime::m_DeltaTimeCheck;
cTimeCheck cGameTime::m_TortalTimeCheck;

cGameTime::cGameTime()
{
	m_TortalTimeCheck.TimerStart();
}

void cGameTime::FrameStart()
{
	m_DeltaTimeCheck.TimerStart();
}

void cGameTime::FrameEnd()
{
	m_DeltaTimeCheck.TimerEnd();
	// �f���^�^�C���̌v�Z
	m_DeltaTime = m_DeltaTimeCheck.GetProcessingTime();
	// �f�o�b�O�ȂǂŒ����Ԏ~�܂����ۂɎ��Ԃ��}���ɐi�ނ��Ƃւ̑΍�
	if (m_DeltaTime > 1.0f)
		m_DeltaTime = 1.0f;
	m_TortalTime = m_TortalTimeCheck.GetAllTime();
}