#pragma once
#include <wrl/client.h>
#include <d3d12.h>
#include <string>
#include "DescriptorBase.h"
#include <memory>

/// <summary>
/// �ЂƂ̃e�N�X�`����ێ�����N���X
/// </summary>
class cTexture {
public:
	cTexture(D3D12_DESCRIPTOR_HEAP_FLAGS flag);			// flag�ϐ��͂ǂ��̃V�F�[�_����ǂ߂�悤�ɂ��邩
	cTexture();
	~cTexture() = default;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetDescriptorHeap();
	inline Microsoft::WRL::ComPtr<ID3D12Resource> GetTextureResource() { return m_pTex; };
	inline std::string GetPath() { return m_FilePath; };
	void SetFilePath(std::string path);
private:
	Microsoft::WRL::ComPtr<ID3D12Resource> m_pTex;		// �e�N�X�`�����\�[�X
	std::shared_ptr<cDescriptorBase> m_DescriptorHeap;
	std::string m_FilePath;
};