#pragma once
#include "ComponentBase.h"
#include <unordered_map>
#include <memory>
#include "Transform.h"

/// <summary>
/// �Q�[�����̊�{�I�Ȃ��ׂẴI�u�W�F�N�g�ɕt�^���邽�߂̃N���X�B
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

	// �X�V�����֐�
	void UpdateBehavior(float deltaTime);			// �p�����ꂽ�N���X��Update���Ă΂��
	void UpdateComponents(float deltaTime);		// �ڑ����ꂽ�R���|�[�l���g��Update���Ă΂��
	virtual void Update(float deltaTime) = 0;		// Update��Ǝ��ɋL�q���邱�ƂŃN���X���L�̓������������

	// �R���|�[�l���g�֐�
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
	cTransform* m_Transform;		// unordered_map����shared_ptr�ŊǗ�����Ă��鐶�A�h���X�Ȃ̂ŉ���̕K�v�Ȃ�
};

template<typename T>
inline T * cBehavior::AddCommponent()
{
	// �܂�map�ɃR���|�[�l���g�����Ă��邩���ׂ�
	int comID = cComponentBase::GetID<T>();
	auto itr = m_ComponentMap.find(comID);        // "xyz" ���ݒ肳��Ă��邩�H
	if (itr == m_ComponentMap.end()) {
		//�ݒ肳��Ă��Ȃ��ꍇ�̏���
		std::shared_ptr<cComponentBase> p(new T(this));
		p->Start();
		m_ComponentMap[comID] = (p);
	}
	return static_cast<T*>(m_ComponentMap[comID].get());
}

template<typename T>
inline void cBehavior::RemoveCommponent()
{
	// �܂�map�ɃR���|�[�l���g�����Ă��邩���ׂ�
	int comID = cComponentBase::GetID<T>();
	auto itr = m_ComponentMap.find(comID);        // "xyz" ���ݒ肳��Ă��邩�H
	if (itr != m_ComponentMap.end()) {
		//�ݒ肳��Ă���ꍇ�̏���
		m_ComponentMap.erase(itr);
	}
}

template<typename T>
inline T * cBehavior::GetCommponent()
{
	// �܂�map�ɃR���|�[�l���g�����Ă��邩���ׂ�
	int comID = cComponentBase::GetID<T>();
	auto itr = m_ComponentMap.find(comID);        // "xyz" ���ݒ肳��Ă��邩�H
	if (itr == m_ComponentMap.end()) {
		// �ݒ肳��Ă��Ȃ�
		return nullptr;
	}
	return static_cast<T*>(m_ComponentMap[comID].get());
}
