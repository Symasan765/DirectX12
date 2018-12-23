#include "UpdateOrder.h"
#include<algorithm>
using namespace std;

std::vector<cBehavior*> cUpdateOrder::m_UpdateActor;

void cUpdateOrder::Update(float deltaTime)
{
	// �폜�Ώۂ�vector�̌㔼�ɏW�߂�
	auto removeIt = remove_if(m_UpdateActor.begin(), m_UpdateActor.end(), [&](cBehavior* value) {
		return value->GetState() == cBehavior::EDead;
	});
	//����ŏ��߂ėv�f���폜�����
	m_UpdateActor.erase(removeIt, m_UpdateActor.end());

	// �X�V���������s
	for (auto& itr : m_UpdateActor) {
		// TODO �ꎞ��~�@�\��t������Ȃ炱���ŏ�������
		itr->UpdateComponents(deltaTime);
		itr->UpdateBehavior(deltaTime);
	}
}

void cUpdateOrder::PushBehavior(cBehavior * ptr)
{
	m_UpdateActor.push_back(ptr);
}