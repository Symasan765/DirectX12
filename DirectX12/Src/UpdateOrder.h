#pragma once
#include <vector>
#include "Behavior.h"

class cUpdateOrder
{
public:
	cUpdateOrder() = default;
	~cUpdateOrder() = default;

	void Update(float deltaTime);
	static void PushBehavior(cBehavior* ptr);
private:
	static std::vector<cBehavior*> m_UpdateActor;
};