#pragma once
#include "MeshRenderer.h"
#include "Render.h"
#include "DXMath.h"
#include <vector>
#include <unordered_map>

/// <summary>
/// cMeshRendererコンポーネントからオブジェクトの描画依頼を受け取るクラス
/// </summary>
class cRenderingOrder
{
public:
	cRenderingOrder() = default;
	~cRenderingOrder() = default;

	static void AddRenderObj(cMeshRenderer* obj,int frameIndex);		// どこからでも登録ができるようにstatic
	void ClearObjs(int frameIndex);		// クリアは実態を持っている場所でのみ可能。描画が終わったあとに実行する
	void RetrunWorldMatrix(DirectX::XMFLOAT4X4* mat,int frameIndex);	// TODO 暫定的に入れてる
private:
	static std::unordered_map<int, std::vector<cMeshRenderer*>> m_ObjMap[Render::g_LatencyNum];
};