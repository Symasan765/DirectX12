#include "MeshRenderer.h"
#include "ModelManager.h"
#include "RenderingOrder.h"
#include "GameTime.h"

cMeshRenderer::cMeshRenderer(cBehavior * owner) : cComponentBase(owner)
{
}

void cMeshRenderer::Update(float deltaTime)
{
}

void cMeshRenderer::Load(std::string fileName, std::string psoName)
{
	m_ResourceID = cModelManager::Load(fileName,psoName);
	m_PsoName = psoName;
	// 描画オブジェクトとして登録しておく
	cRenderingOrder::AddRenderObj(this);
}
