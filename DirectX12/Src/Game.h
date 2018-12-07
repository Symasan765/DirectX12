#pragma once
#include "Window.h"
#include "GameTime.h"

/// <summary>
/// ���C���֐��ō쐬�����S�V�X�e���̊j�ƂȂ�N���X
/// </summary>
class cGameSystem
{
public:
	cGameSystem(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	~cGameSystem();

	void Init();
	void RunLoop();
	void UnInit();
	
private:
	// ����������
	void SystemInit();
	void AppInit();

	// �������
	void AppUnInit();
	void SystemUnInit();

	// ���[�v�̊J�n���A�X�V�A�I��������
	void LoopBegin();
	void GameUpdate();
	void LoopEnd();

	cWindow* m_pWindow = nullptr;
	cGameTime* m_pGameTime = nullptr;

	// WinMain����
	HINSTANCE m_hInst;
	HINSTANCE m_hPrevInstance;
	LPSTR m_lpCmdLine;
	int m_nCmdShow;

	MSG m_Msg;	//���b�Z�[�W�\����
};