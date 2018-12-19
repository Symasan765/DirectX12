#pragma once
#include <string>
#include "DXMath.h"

struct BoneStruct {
	DirectX::XMFLOAT4X4 Offset;
	DirectX::XMFLOAT4X4 Transpose;
	UINT parent;
	std::string name;

	BoneStruct() {
		DirectX::XMStoreFloat4x4(&Offset, DirectX::XMMatrixIdentity());
		DirectX::XMStoreFloat4x4(&Transpose, DirectX::XMMatrixIdentity());
		parent = -1;
	}
};