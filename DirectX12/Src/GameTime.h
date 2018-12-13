#pragma once

#include "TimeCheck.h"

/// <summary>
/// �Q�[���S�̂̎��Ԃ�t���[���̃J�E���g��S������
/// </summary>
class cGameTime
{
public:
	friend class cDXWindow;
	cGameTime();
	~cGameTime() = default;

	void FrameStart();
	void FrameEnd();
	static int FrameIndex();
	static int RenderIndex();
	static float DeltaTime();
	static int TortalFrame();
	static float TortalTime();
private:
	static void SetCurrentBackBufferIndex(UINT idx);

	static float m_DeltaTime;
	static long m_TortalFrame;
	static double m_TortalTime;
	static unsigned m_CurrentIndex;

	static cTimeCheck m_DeltaTimeCheck;
	static cTimeCheck m_TortalTimeCheck;
};