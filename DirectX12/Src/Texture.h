#pragma once
#include <wrl/client.h>
#include <d3d12.h>
#include <string>
#include "DescriptorBase.h"
#include <memory>

/// <summary>
/// ひとつのテクスチャを保持するクラス
/// </summary>
class cTexture {
public:
	cTexture(D3D12_DESCRIPTOR_HEAP_FLAGS flag);			// flag変数はどこのシェーダから読めるようにするか
	cTexture();
	~cTexture() = default;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetDescriptorHeap();
	inline Microsoft::WRL::ComPtr<ID3D12Resource> GetTextureResource() { return m_pTex; };
	inline std::string GetPath() { return m_FilePath; };
	void SetFilePath(std::string path);
private:
	Microsoft::WRL::ComPtr<ID3D12Resource> m_pTex;		// テクスチャリソース
	std::shared_ptr<cDescriptorBase> m_DescriptorHeap;
	std::string m_FilePath;
};