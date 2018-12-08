#pragma once
#include "DescriptorBase.h"
#include "DXMath.h"
#include "Render.h"

class cDepthStencilView : public cDescriptorBase
{
public:
	cDepthStencilView(DXGI_FORMAT format, UINT witdh, UINT height, UINT num,DirectX::XMFLOAT4 color, D3D12_RESOURCE_DIMENSION dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D);
	~cDepthStencilView() = default;

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> m_DsvResource[Render::g_LatencyNum];
};