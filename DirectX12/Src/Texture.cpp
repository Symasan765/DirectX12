#include "Texture.h"
#include "Utility.h"
#include "DirectX12.h"

cTexture::cTexture(D3D12_DESCRIPTOR_HEAP_FLAGS flag)
{
	m_DescriptorHeap = std::make_shared<cDescriptorBase>(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, flag,1);
}

cTexture::cTexture()
{
	m_DescriptorHeap = std::make_shared<cDescriptorBase>(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, 1);
}

Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> cTexture::GetDescriptorHeap()
{
	return m_DescriptorHeap->GetHeap();
}

void cTexture::SetFilePath(std::string path)
{
	m_FilePath = path;
}
