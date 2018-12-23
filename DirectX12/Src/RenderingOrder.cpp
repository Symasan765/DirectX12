#include "RenderingOrder.h"
#include "Behavior.h"

std::unordered_map<int, std::vector<cMeshRenderer*>> cRenderingOrder::m_ObjMap[Render::g_LatencyNum];

void cRenderingOrder::AddRenderObj(cMeshRenderer * obj, int frameIndex)
{
	int ResourceID = obj->ResourceID();
	m_ObjMap[frameIndex][ResourceID].push_back(obj);
}

void cRenderingOrder::ClearObjs(int frameIndex)
{
	m_ObjMap[frameIndex].clear();
}

void cRenderingOrder::RetrunWorldMatrix(DirectX::XMFLOAT4X4 * mat, int frameIndex)
{
	for (int i = 0; i < m_ObjMap[frameIndex][0].size(); i++) {
		mat[i] = m_ObjMap[frameIndex][0][i]->GameObjct()->GetTransform()->ToWorldMatrix(frameIndex);
		DirectX::XMMATRIX matrix = DirectX::XMLoadFloat4x4(&mat[i]);
		matrix = DirectX::XMMatrixTranspose(matrix);
		DirectX::XMStoreFloat4x4(&mat[i], matrix);
	}
}
