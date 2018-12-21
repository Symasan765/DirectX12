#pragma once
#include "ComponentBase.h"
#include <unordered_map>

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
	void UpdateBehavior(float deltaTime);			// �p�����ꂽ�N���X��Update���Ă΂��
	void UpdateComponents(float deltaTime);		// �ڑ����ꂽ�R���|�[�l���g��Update���Ă΂��
	virtual void Update(float deltaTime) = 0;		// Update��Ǝ��ɋL�q���邱�ƂŃN���X���L�̓������������

	// �R���|�[�l���g�֐�
	template <typename T>
	T* AddCommponent();

	template <typename T>
	void RemoveCommponent();

	template <typename T>
	T* GetCommponent();


private:
	State m_State;
	// TODO �R���|�[�l���g�x�[�X�̃e���v���[�g������������@std::unordered_map<int, cComponentBase*> m_ComponentMap;
	// TODO transform�n�̋@�\��ǉ�����
};
