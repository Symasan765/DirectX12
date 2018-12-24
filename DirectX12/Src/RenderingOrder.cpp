#include "RenderingOrder.h"
#include "Behavior.h"

std::unordered_map<std::string, std::vector<cPsoRendrObjData>> cRenderingOrder::m_PsoMap;

void cRenderingOrder::AddRenderObj(cMeshRenderer * obj)
{
	int ResourceID = obj->ResourceID();
	cPsoRendrObjData data;
	data.m_ObjMap[ResourceID].push_back(obj);
	m_PsoMap[obj->GetPsoName()].push_back(data);
}

void cRenderingOrder::RetrunWorldMatrix(DirectX::XMFLOAT4X4 * mat, int frameIndex)
{
	for (auto& itr : m_PsoMap) {
		
	}
}
