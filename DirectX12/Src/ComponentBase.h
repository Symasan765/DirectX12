#pragma once
#include "Behavior.h"

namespace {
	// Component�^�̐����擾����
	int g_TotalComponentTypeNum = 0;
}

/// <summary>
/// �p�������̃R���|�[�l���g�^��n���č쐬����
/// </summary>
template <typename T>
class cComponentBase
{
public:
	virtual ~cComponentBase() = default;
	static int GetID() { return m_ID; };

	virtual bool Start() = 0;
	virtual void Update() = 0;

protected:
	cComponentBase(cBehavior* owner);

	// �R���|�[�l���g����������A�N�^�[
	cBehavior* m_Owner;
	static int m_ID;
};

// ���̌^��ID��ێ�����static�ϐ�
template <typename T>
int cComponentBase<T>::m_ID = -1;

template<typename T>
inline cComponentBase<T>::cComponentBase(cBehavior * owner) : m_Owner(owner)
{
	// ���������B�^��ID���擾����
	if (m_ID == -1) {
		m_ID = g_TotalComponentTypeNum;
		g_TotalComponentTypeNum++;
	}
}
