#pragma once

/// <summary>
/// ���C���֐��ō쐬�����S�V�X�e���̊j�ƂȂ�N���X
/// </summary>
class cGameSystem
{
public:
	cGameSystem();
	~cGameSystem();

	void Init();
	void RunLoop();
	void UnInit();
	
private:
	void SystemInit();
	void AppInit();

	void AppUnInit();
	void SystemUnInit();
};