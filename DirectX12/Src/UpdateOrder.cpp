#include "UpdateOrder.h"
#include<algorithm>
using namespace std;

std::vector<cBehavior*> cUpdateOrder::m_UpdateActor;

void cUpdateOrder::Update(float deltaTime)
{
	// 削除対象をvectorの後半に集める
	auto removeIt = remove_if(m_UpdateActor.begin(), m_UpdateActor.end(), [&](cBehavior* value) {
		return value->GetState() == cBehavior::EDead;
	});
	//これで初めて要素が削除される
	m_UpdateActor.erase(removeIt, m_UpdateActor.end());

	// 更新処理を実行
	for (auto& itr : m_UpdateActor) {
		// TODO 一時停止機能を付加するならここで処理する
		itr->UpdateComponents(deltaTime);
		itr->UpdateBehavior(deltaTime);
	}
}

void cUpdateOrder::PushBehavior(cBehavior * ptr)
{
	m_UpdateActor.push_back(ptr);
}