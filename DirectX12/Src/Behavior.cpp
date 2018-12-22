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
	// ついている全てのコンポーネントの更新を実行する
	for (auto itr = m_ComponentMap.begin(); itr != m_ComponentMap.end(); ++itr) {
		itr->second->Update(deltaTime);
	}
}
