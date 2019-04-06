#include "TextureLoader.h"
#include "Utility.h"
#include <WICTextureLoader.h>
#include <d3dx12.h>
#include <vector>

using namespace Microsoft::WRL;
using namespace DirectX;

std::shared_ptr<cResourceCreateCommand> cTextureLoader::m_Command;
bool cTextureLoader::m_InitFlag = false;

void cTextureLoader::LoadTextureFromFile(std::string fileName, cTexture * texture)
{
	if (m_InitFlag == false) {
		Init();
	}

	ComPtr<ID3D12Resource> textureUploadHeap;		// �ꎞ�ϐ��ł悵
	ID3D12DescriptorHeap* srvHeap = texture->GetDescriptorHeap().Get();
	ID3D12Resource* tex = texture->GetTextureResource().Get();
	
	// string��wstring�֕ϊ�����
	std::wstring wStr = std::wstring(fileName.begin(), fileName.end());
	const UINT subresoucesize = 1;

	ResourceLoading(wStr, tex, textureUploadHeap, subresoucesize);
	SetBarrier(tex);
	CreateShaderResourceView(tex, srvHeap, textureUploadHeap, subresoucesize);
	ResourceUpload();

	texture->SetFilePath(fileName);	// �p�X��o�^���Ă���
}

void cTextureLoader::Init()
{
	m_Command = std::make_shared<cResourceCreateCommand>();
	m_InitFlag = true;
}

void cTextureLoader::ResourceLoading(std::wstring& wStr, ID3D12Resource*& tex, ComPtr<ID3D12Resource>& textureUploadHeap, const UINT subresoucesize)
{
	// �e�N�X�`�������[�h����
	std::unique_ptr<uint8_t[]> textureData;
	D3D12_SUBRESOURCE_DATA subresouceData;
	CheckHR(LoadWICTextureFromFile(cDirectX12::GetDevice(),
		wStr.c_str(),
		&tex,
		textureData,
		subresouceData));

	// �f�[�^�̃A�b�v���[�h�Ɏg�p����o�b�t�@�̕K�v�ȃT�C�Y���擾�B

	const UINT64 uploadBufferSize
		= GetRequiredIntermediateSize(tex, 0, subresoucesize);

	// �A�b�v���[�h�p�o�b�t�@�̍쐬
	CheckHR(cDirectX12::GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&textureUploadHeap)));

	auto commandList = m_Command.get()->GetList();
	commandList->Reset(m_Command->GetAlloc().Get(), nullptr);

	// �T�u���\�[�X�̍X�V
	UpdateSubresources(commandList.Get(),
		tex,										// �X�V��A�h���X
		textureUploadHeap.Get(),		// ���ԃA�h���X
		0,											// �I�t�Z�b�g�l
		0,											// ���\�[�X���̍ŏ��̃T�u���\�[�X�̃C���f�b�N�X
		subresoucesize,					// ���\�[�X���̃T�u���\�[�X�̐�
		&subresouceData);					// �X�V�ɗ��p����T�u���\�[�X�f�[�^���܂ޔz��A�h���X
	tex->SetName(L"TextureResource");
}

void cTextureLoader::SetBarrier(ID3D12Resource*& tex)
{
	// �o���A�̐ݒu
	m_Command->GetList()->ResourceBarrier(1,
		&CD3DX12_RESOURCE_BARRIER::Transition(tex,
			D3D12_RESOURCE_STATE_COPY_DEST,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
}

void cTextureLoader::CreateShaderResourceView(ID3D12Resource*& tex, ID3D12DescriptorHeap*& srvHeap, Microsoft::WRL::ComPtr<ID3D12Resource>& textureUploadHeap, const UINT subresoucesize)
{
	D3D12_RESOURCE_DESC textureDesc = tex->GetDesc();

	// Describe and create a SRV for the texture.
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = textureDesc.Format;	// �e�N�X�`���t�H�[�}�b�g(TK���擾���Ă��ꂽ���́B��{RGBA8)
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = subresoucesize;
	cDirectX12::GetDevice()->CreateShaderResourceView(tex,
		&srvDesc,
		srvHeap->GetCPUDescriptorHandleForHeapStart());

	// �s�v�ɂȂ������ԃf�[�^��j������R�}���h
	m_Command->GetList().Get()->DiscardResource(textureUploadHeap.Get(), nullptr);
}

void cTextureLoader::ResourceUpload()
{
	// Close the command list and execute it to begin the initial GPU setup.
	CheckHR(m_Command->GetList()->Close());
	ID3D12CommandList* ppCommandLists[] = { m_Command->GetList().Get() };
	m_Command->GetQueue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	// GPU�ɃA�b�v���[�h�����̂�҂�
	cFenceObj FenceObj;
	FenceObj.WaitForPreviousFrame(m_Command->GetQueue().Get());
}
