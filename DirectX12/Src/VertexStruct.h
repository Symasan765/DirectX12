#pragma once
#include <Windows.h>
#include <DirectXMath.h>

struct DefaultVertex {
	DirectX::XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 normal = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT2 texcoord = { 0.0f,0.0f };
	DirectX::XMFLOAT3 tangent = { 0.0f,0.0f,0.0f };
	DirectX::XMINT4 bindex = { 0,0,0,0 };					// 影響するボーンインデックス
	DirectX::XMFLOAT4 bweight = { 0.0f,0.0f,0.0f,0.0f };	// 各ボーンの重み情報
};

struct VERTEX_TEST {
	DirectX::XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 normal = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT2 texcoord = { 0.0f,0.0f };
};

struct ScreenQuadVertex
{
	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT2 texcoord;
};