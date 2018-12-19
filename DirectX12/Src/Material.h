#pragma once
#include <vector>
#include "Texture.h"

/// <summary>
/// マテリアルを保持するクラス
/// </summary>
class cMaterial
{
public:
	cMaterial() = default;
	~cMaterial() = default;

	void DataSet(const std::vector<cTexture>& textures);
	void SetTexture(ID3D12GraphicsCommandList * cmdList, UINT RootParameterIndex);
private:
	std::vector<cTexture> m_Tex;
};