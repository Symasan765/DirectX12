#pragma once
#include "Behavior.h"

class cPlayer : public cBehavior
{
public:
	cPlayer();
	~cPlayer() = default;
	void Update(float deltaTime);
private:

};

// TODO �����܂ł����e�X�g�p��Scene�Ȃ̂Ō�X����
class cTestScene
{
public:
	cTestScene();
	~cTestScene();

private:
	cPlayer m_Player;
};