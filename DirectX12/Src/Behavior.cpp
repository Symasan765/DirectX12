#include "Behavior.h"
#include "UpdateOrder.h"

cBehavior::cBehavior()
{
	// システムにオブジェクトを登録する
	cUpdateOrder::PushBehavior(this);

	// 必ずトランスフォームコンポーネントは接続してアドレスを持っておく。
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
	// ついている全てのコンポーネントの更新を実行する
	for (auto itr = m_ComponentMap.begin(); itr != m_ComponentMap.end(); ++itr) {
		itr->second->Update(deltaTime);
	}
}
