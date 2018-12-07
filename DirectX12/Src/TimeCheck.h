#pragma once
#include <Windows.h>

/// <summary>
/// ���Ԍv�����s���N���X
/// </summary>
class cTimeCheck {
public:
	cTimeCheck();
	~cTimeCheck() = default;					//��������Ƃ��ɂȂ�����
	void TimerStart();
	void TimerEnd();
	float GetProcessingTime()const;		//���������������Ԃ�float�ŕԂ��֐�
	float GetAllTime()const;
private:
	LARGE_INTEGER m_Start, m_End;		//�����J�n�̎��ԂƏI�����Ԃ��i�[����ϐ�
	static LARGE_INTEGER m_Freq;		//�P�ʎ��Ԃ��i�[�B�֐��ŋ��߂����l�����̒l�Ŋ����sec�P�ʂɕϊ��ł���B
};