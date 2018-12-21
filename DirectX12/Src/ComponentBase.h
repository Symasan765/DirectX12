#pragma once
#include "Behavior.h"

namespace {
	// Component型の数を取得する
	int g_TotalComponentTypeNum = 0;
}

/// <summary>
/// 継承する先のコンポーネント型を渡して作成する
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

	// コンポーネントを所持するアクター
	cBehavior* m_Owner;
	static int m_ID;
};

// その型のIDを保持するstatic変数
template <typename T>
int cComponentBase<T>::m_ID = -1;

template<typename T>
inline cComponentBase<T>::cComponentBase(cBehavior * owner) : m_Owner(owner)
{
	// 未初期化。型のIDを取得する
	if (m_ID == -1) {
		m_ID = g_TotalComponentTypeNum;
		g_TotalComponentTypeNum++;
	}
}
