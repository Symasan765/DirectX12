#include "TestScene.h"
#include "ModelManager.h"
#include "MeshRenderer.h"

cTestScene::cTestScene()
{
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
	m_Transform->Rotation().y += 360.0f * (3.141592653 / 180) * deltaTime;
	m_Transform->Scale().x = 10.0f;
	m_Transform->Scale().y = 10.0f;
	m_Transform->Scale().z = 10.0f;
}
