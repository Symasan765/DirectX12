#pragma once
#include "Main.h"
#include "InputLayout.h"
#include "ShaderByte.h"
#include "RootSignature.h"
#include <memory>
#include <vector>

/// <summary>
/// PSOを一括りに作成するクラス
/// </summary>
class cPipelineStateObj
{
public:
	friend class cPSOManager;
	void CreatePipelineState();

	// 他の設定項目への対応は暫定的にオブジェクト自体を渡して行う
	inline D3D12_GRAPHICS_PIPELINE_STATE_DESC* GetPipelineDESC() { return &psoDesc; };
	inline Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPipelineState() { return m_Pso; };

	// 設定用オブジェクトの取得関数
	std::shared_ptr<cRootSignature> GetSettingRootSignature() {
		return m_pRootSignature;
	};
	std::shared_ptr<cShaderByte> GetSettingShaderByte() {
		return m_pShaderByte;
	};
	std::shared_ptr<cInputLayout> GetSettingInputLayout() {
		return m_pInputLayout;
	};
	std::vector<DXGI_FORMAT>& GetSettingRtvFormat() {
		return m_RtvFormat;
	};
private:
	cPipelineStateObj(std::string psoName);	// cPSOManagerクラスから作成する
	~cPipelineStateObj() = default;
	//=====以下の関数は設定必須======
	void RenderTargetSetting(DXGI_FORMAT* format, unsigned RTNum);
	void ShaderBytecodeSetting(ID3D10Blob* vs, ID3D10Blob* ps, ID3D10Blob* ds = nullptr, ID3D10Blob* hs = nullptr, ID3D10Blob* gs = nullptr);
	void ShaderBytecodeSetting(cShaderByte* pShaderData);
	void RootSignatureSetting(ID3D12RootSignature* rs);
	void InputLayoutSetting(D3D12_INPUT_ELEMENT_DESC* inputLayout, unsigned num);
	void InputLayoutSetting(cInputLayout* inputLayout);
	// ==========================

	Microsoft::WRL::ComPtr<ID3D12PipelineState> m_Pso;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};

	std::shared_ptr<cRootSignature> m_pRootSignature;
	std::shared_ptr<cShaderByte> m_pShaderByte;
	std::shared_ptr<cInputLayout> m_pInputLayout;
	std::vector<DXGI_FORMAT> m_RtvFormat;

	std::string m_PsoName;		// このオブジェクトの名前
};