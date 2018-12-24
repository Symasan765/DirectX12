#include "RenderingOrder.h"
#include "Behavior.h"

std::map<UINT, std::vector<cMeshRenderer*>> cRenderingOrder::m_ObjMap;

void cRenderingOrder::AddRenderObj(cMeshRenderer * obj)
{
	int ResourceID = obj->ResourceID();
	m_ObjMap[ResourceID].push_back(obj);
}

void cRenderingOrder::RetrunWorldMatrix(int resourceID, DirectX::XMFLOAT4X4 * mat, int frameIndex)
{
	for (int i = 0; i < m_ObjMap[resourceID].size(); i++) {
		mat[i] = m_ObjMap[resourceID][i]->GameObjct()->GetTransform()->ToWorldMatrix(frameIndex);
		DirectX::XMMATRIX matrix = DirectX::XMLoadFloat4x4(&mat[i]);
		matrix = DirectX::XMMatrixTranspose(matrix);
		DirectX::XMStoreFloat4x4(&mat[i], matrix);
	}
}
