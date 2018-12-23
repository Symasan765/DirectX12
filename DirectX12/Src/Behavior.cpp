#include "Behavior.h"
#include "UpdateOrder.h"

cBehavior::cBehavior()
{
	// �V�X�e���ɃI�u�W�F�N�g��o�^����
	cUpdateOrder::PushBehavior(this);

	// �K���g�����X�t�H�[���R���|�[�l���g�͐ڑ����ăA�h���X�������Ă����B
	m_Transform = AddCommponent<cTransform>();
}

cBehavior::~cBehavior()
{
	m_State = EDead;
}

void cBehavior::UpdateBehavior(float deltaTime)
{
	Update(deltaTime);
}

void cBehavior::UpdateComponents(float deltaTime)
{
	// ���Ă���S�ẴR���|�[�l���g�̍X�V�����s����
	for (auto itr = m_ComponentMap.begin(); itr != m_ComponentMap.end(); ++itr) {
		itr->second->Update(deltaTime);
	}
}
