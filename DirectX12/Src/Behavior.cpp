#include "Behavior.h"

cBehavior::~cBehavior()
{

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
