#pragma once
#include "ComponentBase.h"
#include "DXMath.h"

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

	DirectX::XMFLOAT4 m_Position;
	DirectX::XMFLOAT4 m_Rotation;
	DirectX::XMFLOAT4 m_Scale;
};