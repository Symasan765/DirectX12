#include "GameTime.h"
#include "Render.h"

float cGameTime::m_DeltaTime = 0;
long cGameTime::m_TortalFrame = 0;
double cGameTime::m_TortalTime = 0;
unsigned cGameTime::m_CurrentIndex = 0;
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
	// デルタタイムの計算
	m_DeltaTime = m_DeltaTimeCheck.GetProcessingTime();
	// デバッグなどで長期間止まった際に時間が急激に進むことへの対策
	if (m_DeltaTime > 1.0f)
		m_DeltaTime = 1.0f;
	m_TortalTime = m_TortalTimeCheck.GetAllTime();
	m_TortalFrame++;
}

int cGameTime::FrameIndex()
{
	return (m_CurrentIndex + (Render::g_LatencyNum - 1)) % Render::g_LatencyNum;
}

int cGameTime::RenderIndex()
{
	return m_CurrentIndex;
}

float cGameTime::DeltaTime()
{
	return m_DeltaTime;
}

int cGameTime::TortalFrame()
{
	return m_TortalFrame;
}

float cGameTime::TortalTime()
{
	return (float)m_TortalTime;
}

void cGameTime::SetCurrentBackBufferIndex(UINT idx)
{
	m_CurrentIndex = idx;
}
