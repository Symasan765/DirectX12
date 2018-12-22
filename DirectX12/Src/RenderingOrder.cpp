#include "RenderingOrder.h"

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
