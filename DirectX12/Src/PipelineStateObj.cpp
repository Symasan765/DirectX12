#include "PipelineStateObj.h"
#include <d3dx12.h>
#include "Utility.h"
#include "DirectX12.h"
#include "InputLayout.h"
#include "ShaderByte.h"

std::unordered_map<std::string, UINT> cPipelineStateObj::m_PriorityMap;

cPipelineStateObj::cPipelineStateObj(std::string psoName)
{
	m_pRootSignature = std::make_shared<cRootSignature>();
	m_pShaderByte = std::make_shared<cShaderByte>();
	m_pInputLayout = std::make_shared<cInputLayout>();
	m_PsoName = psoName;

	// 暫定的な初期化。今後、ここらも変更できるようにする可能性あり
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(CD3DX12_DEFAULT());
	psoDesc.BlendState = CD3DX12_BLEND_DESC(CD3DX12_DEFAULT());
	psoDesc.DepthStencilState.DepthEnable = true;
	psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	psoDesc.DepthStencilState.StencilEnable = false;
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	psoDesc.SampleDesc.Count = 1;
}

void cPipelineStateObj::CreatePipelineState(UINT priority)
{
	// 各設定用オブジェの作成を行う
	m_pRootSignature->CreateCommit();
	InputLayoutSetting(m_pInputLayout.get());
	if (m_RtvFormat.size() > 0)
		RenderTargetSetting(&m_RtvFormat[0], (unsigned)m_RtvFormat.size());
	RootSignatureSetting(m_pRootSignature->GetRootSignature().Get());
	ShaderBytecodeSetting(m_pShaderByte.get());

#ifdef _DEBUG
	// マップの多重登録チェック
	auto itr = m_PriorityMap.find(m_PsoName);        // "xyz" が設定されているか？
	if (itr != m_PriorityMap.end()) {
		_ASSERT_EXPR(true, _T("同じ名前のPSOが作成されようとしています"));
	}
#endif

	m_PriorityMap[m_PsoName] = priority * PipelineStateObjParam::g_PriorityRate;	// 優先度を保存

	CheckHR(cDirectX12::GetDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(m_Pso.ReleaseAndGetAddressOf())));
}

UINT cPipelineStateObj::GetPsoPriority(std::string psoName)
{
	return m_PriorityMap[psoName];
}

void cPipelineStateObj::RenderTargetSetting(DXGI_FORMAT * format, unsigned RTNum)
{
	psoDesc.NumRenderTargets = RTNum;

	for (unsigned i = 0; i < RTNum; i++)
		psoDesc.RTVFormats[i] = format[i];
}

void cPipelineStateObj::ShaderBytecodeSetting(ID3D10Blob * vs, ID3D10Blob * ps, ID3D10Blob * ds, ID3D10Blob * hs, ID3D10Blob * gs)
{
	if (vs != nullptr) {
		psoDesc.VS.pShaderBytecode = vs->GetBufferPointer();
		psoDesc.VS.BytecodeLength = vs->GetBufferSize();
	}

	if (ps != nullptr) {
		psoDesc.PS.pShaderBytecode = ps->GetBufferPointer();
		psoDesc.PS.BytecodeLength = ps->GetBufferSize();
	}

	if (ds != nullptr) {
		psoDesc.DS.pShaderBytecode = ds->GetBufferPointer();
		psoDesc.DS.BytecodeLength = ds->GetBufferSize();
	}

	if (hs != nullptr) {
		psoDesc.HS.pShaderBytecode = hs->GetBufferPointer();
		psoDesc.HS.BytecodeLength = hs->GetBufferSize();
	}

	if (gs != nullptr) {
		psoDesc.GS.pShaderBytecode = gs->GetBufferPointer();
		psoDesc.GS.BytecodeLength = gs->GetBufferSize();
	}
}

void cPipelineStateObj::ShaderBytecodeSetting(cShaderByte * pShaderData)
{
	auto& data = pShaderData->GetShaderData();
	ShaderBytecodeSetting(data.vs, data.ps, data.ds, data.hs, data.gs);
}

void cPipelineStateObj::RootSignatureSetting(ID3D12RootSignature * rs)
{
	psoDesc.pRootSignature = rs;
}

void cPipelineStateObj::InputLayoutSetting(D3D12_INPUT_ELEMENT_DESC * inputLayout, unsigned num)
{
	psoDesc.InputLayout.NumElements = num;
	psoDesc.InputLayout.pInputElementDescs = inputLayout;
}

void cPipelineStateObj::InputLayoutSetting(cInputLayout * inputLayout)
{
	psoDesc.InputLayout.NumElements = (UINT)inputLayout->GetSize();
	psoDesc.InputLayout.pInputElementDescs = inputLayout->GetInputElementDesc();
}

