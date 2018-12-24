#pragma once
#include "MeshRenderer.h"
#include "Render.h"
#include "DXMath.h"
#include <vector>
#include <map>

/// <summary>
/// cMeshRendererコンポーネントからオブジェクトの描画依頼を受け取るクラス
/// </summary>
class cRenderingOrder
{
public:
	cRenderingOrder() = default;
	~cRenderingOrder() = default;

	static void AddRenderObj(cMeshRenderer* obj);		// どこからでも登録ができるようにstatic
	void RetrunWorldMatrix(int resourceID,DirectX::XMFLOAT4X4* mat,int frameIndex);	// TODO 暫定的に入れてる
	std::map<UINT, std::vector<cMeshRenderer*>>& GetMapObj() { return m_ObjMap; };
private:
	static std::map<UINT, std::vector<cMeshRenderer*>> m_ObjMap;
};