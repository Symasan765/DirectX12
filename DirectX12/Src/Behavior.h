#pragma once
#include "ComponentBase.h"
#include <unordered_map>

/// <summary>
/// ゲーム中の基本的なすべてのオブジェクトに付与するためのクラス。
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

	// 更新処理関数
	void UpdateBehavior(float deltaTime);			// 継承されたクラスのUpdateが呼ばれる
	void UpdateComponents(float deltaTime);		// 接続されたコンポーネントのUpdateが呼ばれる
	virtual void Update(float deltaTime) = 0;		// Updateを独自に記述することでクラス特有の動作を実現する

	// コンポーネント関数
	template <typename T>
	T* AddCommponent();

	template <typename T>
	void RemoveCommponent();

	template <typename T>
	T* GetCommponent();


private:
	State m_State;
	// TODO コンポーネントベースのテンプレート問題を解決する　std::unordered_map<int, cComponentBase*> m_ComponentMap;
	// TODO transform系の機能を追加する
};
