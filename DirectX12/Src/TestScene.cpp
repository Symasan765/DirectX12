#include "TestScene.h"
#include "ModelManager.h"
#include "MeshRenderer.h"

cTestScene::cTestScene()
{
	cModelManager::Load("Link.x");
}

cTestScene::~cTestScene()
{
}

cPlayer::cPlayer()
{
	auto renderer = AddCommponent<cMeshRenderer>();
	renderer->Load("Link.x", "Main");
}

void cPlayer::Update(float deltaTime)
{

}
