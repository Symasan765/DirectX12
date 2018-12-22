#include "Transform.h"
#include "GameTime.h"
using namespace DirectX;

cTransform::cTransform(cBehavior * owner) : cComponentBase(owner)
{

}

DirectX::XMFLOAT4X4 cTransform::ToWorldMatrix(int frameIndex)
{
	XMMATRIX mat = XMMatrixScaling(m_Scale[frameIndex].x, m_Scale[frameIndex].y, m_Scale[frameIndex].z);
	mat *= XMMatrixRotationRollPitchYaw(m_Rotation[frameIndex].x, m_Rotation[frameIndex].y, m_Rotation[frameIndex].z);
	mat *= XMMatrixTranslation(m_Position[frameIndex].x, m_Position[frameIndex].y, m_Position[frameIndex].z);

	XMFLOAT4X4 ret;
	XMStoreFloat4x4(&ret, mat);
	return ret;
}

DirectX::XMFLOAT4 & cTransform::Position()
{
	return m_Position[cGameTime::FrameIndex()];
}

DirectX::XMFLOAT4 & cTransform::Rotation()
{
	return m_Rotation[cGameTime::FrameIndex()];
}

DirectX::XMFLOAT4 & cTransform::Scale()
{
	return m_Scale[cGameTime::FrameIndex()];
}
