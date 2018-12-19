#include "TestScene.h"
#include "ModelManager.h"

cTestScene::cTestScene()
{
	cModelManager::Load("Link.x");
}

cTestScene::~cTestScene()
{
}
