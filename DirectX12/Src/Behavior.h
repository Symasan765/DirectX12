#pragma once
#include "ComponentBase.h"
#include <unordered_map>
#include <memory>
#include "Transform.h"

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

	State GetState() { return m_State; };
private:
	State m_State = EActive;
	std::unordered_map<int, std::shared_ptr<cComponentBase>> m_ComponentMap;
protected:
	cTransform* m_Transform;		// unordered_map内のshared_ptrで管理されている生アドレスなので解放の必要なし
};

template<typename T>
inline T * cBehavior::AddCommponent()
{
	// まずmapにコンポーネントがついているか調べる
	int comID = cComponentBase::GetID<T>();
	auto itr = m_ComponentMap.find(comID);        // "xyz" が設定されているか？
	if (itr == m_ComponentMap.end()) {
		//設定されていない場合の処理
		std::shared_ptr<cComponentBase> p(new T(this));
		p->Start();
		m_ComponentMap[comID] = (p);
	}
	return static_cast<T*>(m_ComponentMap[comID].get());
}

template<typename T>
inline void cBehavior::RemoveCommponent()
{
	// まずmapにコンポーネントがついているか調べる
	int comID = cComponentBase::GetID<T>();
	auto itr = m_ComponentMap.find(comID);        // "xyz" が設定されているか？
	if (itr != m_ComponentMap.end()) {
		//設定されている場合の処理
		m_ComponentMap.erase(itr);
	}
}

template<typename T>
inline T * cBehavior::GetCommponent()
{
	// まずmapにコンポーネントがついているか調べる
	int comID = cComponentBase::GetID<T>();
	auto itr = m_ComponentMap.find(comID);        // "xyz" が設定されているか？
	if (itr == m_ComponentMap.end()) {
		// 設定されていない
		return nullptr;
	}
	return static_cast<T*>(m_ComponentMap[comID].get());
}
