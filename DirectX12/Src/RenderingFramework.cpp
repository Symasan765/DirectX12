#include "RenderingFramework.h"
#include "DXMath.h"

cRenderingFramework::cRenderingFramework()
{
	m_PsoManager = std::make_unique<cPSOManager>();
	CreatePSO();
}

void cRenderingFramework::Draw(std::shared_ptr<cCommandSystem> m_CommandSystem, int frameIndex)
{

}

void cRenderingFramework::Execute(std::shared_ptr<cCommandQueue> queue, int frameIndex)
{

}

void cRenderingFramework::CreatePSO()
{
	auto pso = m_PsoManager->RequestPSO("Main");
	auto rootSig = pso->GetSettingRootSignature();
	auto shaderByte = pso->GetSettingShaderByte();
	auto inputLayout = pso->GetSettingInputLayout();
	auto& format = pso->GetSettingRtvFormat();

	rootSig->AddSamplers(0);
	rootSig->AddCBV(0);
	rootSig->AddCBV(1);
	rootSig->AddCBV(2);
	rootSig->AddCBV(3);
	rootSig->AddSRV(0);

	shaderByte->CompileFromFile("HLSL/PBR.hlsl", "VSMain", "PSMain");

	inputLayout->AddElement<DirectX::XMFLOAT3>("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	inputLayout->AddElement<DirectX::XMFLOAT3>("NORMAL", DXGI_FORMAT_R32G32B32_FLOAT);
	inputLayout->AddElement<DirectX::XMFLOAT2>("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);
	inputLayout->AddElement<DirectX::XMFLOAT3>("TANGENT", DXGI_FORMAT_R32G32B32_FLOAT);
	inputLayout->AddElement<DirectX::XMINT4>("BONEINDEX", DXGI_FORMAT_R32G32B32A32_SINT);
	inputLayout->AddElement<DirectX::XMFLOAT4>("WEIGHT", DXGI_FORMAT_R32G32B32A32_FLOAT);
	inputLayout->AddElement<DirectX::XMFLOAT4>("MATRIX", DXGI_FORMAT_R32G32B32A32_FLOAT, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 0, 1, 1);
	inputLayout->AddElement<DirectX::XMFLOAT4>("MATRIX", DXGI_FORMAT_R32G32B32A32_FLOAT, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1, 1, 1);
	inputLayout->AddElement<DirectX::XMFLOAT4>("MATRIX", DXGI_FORMAT_R32G32B32A32_FLOAT, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 2, 1, 1);
	inputLayout->AddElement<DirectX::XMFLOAT4>("MATRIX", DXGI_FORMAT_R32G32B32A32_FLOAT, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 3, 1, 1);

	format.push_back(DXGI_FORMAT_R8G8B8A8_UNORM);
	pso->CreatePipelineState();
}
