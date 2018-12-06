#pragma once

class cComponent;

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
	void UpdateBehavior(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void Update(float deltaTime) = 0;		// Updateを独自に記述することでクラス特有の動作を実現する

	// コンポーネント関数
	void AddCommponent(cComponent* pComponent);


private:
	State m_State;
	// TODO transform系の機能を追加する
};
