#pragma once
#include <vector>
#include "Texture.h"

/// <summary>
/// �}�e���A����ێ�����N���X
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