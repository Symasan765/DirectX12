#pragma once
#include "ComponentBase.h"
#include "DXMath.h"
#include "Render.h"

/// <summary>
/// オブジェクトの位置や回転、サイズなどを管理する
/// </summary>
class cTransform : public cComponentBase
{
public:
	cTransform(cBehavior* owner);
	~cTransform() = default;

	void Update(float deltaTime) {};
	void Start() {};

	DirectX::XMFLOAT4X4 ToWorldMatrix(int frameIndex);
	DirectX::XMFLOAT4& Position();
	DirectX::XMFLOAT4& Rotation();
	DirectX::XMFLOAT4& Scale();

private:
	// 描画と更新を並列で行うのでダブルバッファ化
	DirectX::XMFLOAT4 m_Position[Render::g_LatencyNum];
	DirectX::XMFLOAT4 m_Rotation[Render::g_LatencyNum];
	DirectX::XMFLOAT4 m_Scale[Render::g_LatencyNum];
};