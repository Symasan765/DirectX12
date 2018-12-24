#pragma once
#include "MeshRenderer.h"
#include "Render.h"
#include "DXMath.h"
#include <vector>
#include <unordered_map>

struct cPsoRendrObjData {
	std::unordered_map<int, std::vector<cMeshRenderer*>> m_ObjMap;
};

/// <summary>
/// cMeshRendererコンポーネントからオブジェクトの描画依頼を受け取るクラス
/// </summary>
class cRenderingOrder
{
public:
	cRenderingOrder() = default;
	~cRenderingOrder() = default;

	static void AddRenderObj(cMeshRenderer* obj);		// どこからでも登録ができるようにstatic
	void RetrunWorldMatrix(DirectX::XMFLOAT4X4* mat,int frameIndex);	// TODO 暫定的に入れてる
private:
	static std::unordered_map<std::string, std::vector<cPsoRendrObjData>> m_PsoMap;
};