#pragma once
class cBehavior;

namespace {
	// Component�^�̐���ێ�����
	int g_TotalComponentTypeNum = 0;
}

/// <summary>
/// �p�������̃R���|�[�l���g�^��n���č쐬����
/// </summary>
class cComponentBase
{
public:
	virtual ~cComponentBase() = default;
	virtual void Update(float deltaTime) = 0;
	virtual void Start() = 0;

	template <typename T>
	static int GetID();
protected:
	cComponentBase(cBehavior * owner)
	{
		m_Owner = owner;
	}

	// �R���|�[�l���g����������A�N�^�[
	cBehavior* m_Owner;
private:
	// �V�����R���|�[�l���gID��ێ����Ă���֐�
	static int NewID() {
		static int ID = 0;
		ID++;
		return ID;
	}
};

/// <summary>
/// �K���r�w�C�r�A�̒ǉ��֐����ŌĂ΂�邱�ƂɂȂ�
/// </summary>
template<typename T>
inline int cComponentBase::GetID()
{
	static int ID = -1;		// �e���v���[�g�̌^���Ƃɗp�ӂ����
	if (ID == -1) {
		// �Ăяo���ꂽ�^����ID���U���邱�ƂɂȂ�
		ID = NewID();
	}
	return ID;
}