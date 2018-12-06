#pragma once

class cComponent;

/// <summary>
/// �Q�[�����̊�{�I�Ȃ��ׂẴI�u�W�F�N�g�ɕt�^���邽�߂̃N���X�B
/// </summary>
class cBehavior
{
public:
	enum State {
		EActive = 0,
		EPaused,
		EDead,
	};
	cBehavior();
	virtual ~cBehavior();

	// �X�V�����֐�
	void UpdateBehavior(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void Update(float deltaTime) = 0;		// Update��Ǝ��ɋL�q���邱�ƂŃN���X���L�̓������������

	// �R���|�[�l���g�֐�
	void AddCommponent(cComponent* pComponent);


private:
	State m_State;
	// TODO transform�n�̋@�\��ǉ�����
};
