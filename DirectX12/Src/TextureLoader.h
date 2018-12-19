#pragma once
#include "Texture.h"
#include "DirectX12.h"
#include "FenceObj.h"
#include <string>
#include "ResourceCreateCommand.h"

class cTextureLoader {
public:
	friend class cGameSystem;
	static void LoadTextureFromFile(std::string fileName, cTexture* texture);
private:
	cTextureLoader() = default;
	~cTextureLoader() = default;
	static void Init();
	static void ResourceLoading(std::wstring& wStr, ID3D12Resource*& tex, Microsoft::WRL::ComPtr<ID3D12Resource>& textureUploadHeap, const UINT subresoucesize);
	static void SetBarrier(ID3D12Resource*& tex);
	static void CreateShaderResourceView(ID3D12Resource*& tex, ID3D12DescriptorHeap*& srvHeap, Microsoft::WRL::ComPtr<ID3D12Resource>& textureUploadHeap, const UINT subresoucesize);
	static void ResourceUpload();

	static std::shared_ptr<cResourceCreateCommand> m_Command;
	static bool m_InitFlag;
};