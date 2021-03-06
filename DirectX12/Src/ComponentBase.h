#pragma once
class cBehavior;

namespace {
	// Component型の数を保持する
	int g_TotalComponentTypeNum = 0;
}

/// <summary>
/// 継承する先のコンポーネント型を渡して作成する
/// </summary>
class cComponentBase
{
public:
	virtual ~cComponentBase() = default;
	virtual void Update(float deltaTime) = 0;
	virtual void Start() = 0;

	template <typename T>
	static int GetID();

	cBehavior* GameObjct() { return m_Owner; };
protected:
	cComponentBase(cBehavior * owner)
	{
		m_Owner = owner;
	}

	// コンポーネントを所持するアクター
	cBehavior* m_Owner;
private:
	// 新しいコンポーネントIDを保持している関数
	static int NewID() {
		static int ID = 0;
		ID++;
		return ID;
	}
};

/// <summary>
/// 必ずビヘイビアの追加関数内で呼ばれることになる
/// </summary>
template<typename T>
inline int cComponentBase::GetID()
{
	static int ID = -1;		// テンプレートの型ごとに用意される
	if (ID == -1) {
		// 呼び出された型順にIDが振られることになる
		ID = NewID();
	}
	return ID;
}