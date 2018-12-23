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

	m_Transform->Scale().x += 100.0f;
	m_Transform->Scale().y += 100.0f;
	m_Transform->Scale().z += 100.0f;
}

void cPlayer::Update(float deltaTime)
{
	m_Transform->Rotation().y += 0.1f;
	m_Transform->Scale().x = 10.0f;
	m_Transform->Scale().y = 10.0f;
	m_Transform->Scale().z = 10.0f;
}
