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

// TODO あくまでも仮テスト用のSceneなので後々消す
class cTestScene
{
public:
	cTestScene();
	~cTestScene();

private:
	cPlayer m_Player;
};