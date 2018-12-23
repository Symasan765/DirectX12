#include "RenderingFramework.h"
#include "DXMath.h"
#include "Utility.h"

#include "RenderingOrder.h"
#include "DXWindow.h"
#include "ModelManager.h"

using namespace DirectX;

cRenderingFramework::cRenderingFramework()
{
	m_PsoManager = std::make_unique<cPSOManager>();
	CreatePSO();

	// TODO ここ消す
	XMMATRIX  viewMat, projMat;
	viewMat = XMMatrixLookAtLH({ 0, 0.5f, -10.5f }, { 0, 0.0f, 0 }, { 0, 1, 0 });
	projMat = XMMatrixPerspectiveFovLH(45, (float)1920 / 1080, 0.01f, 50.0f);
	auto mvpMat = XMMatrixTranspose(viewMat * projMat);

	auto worldTransMat = XMMatrixTranspose(viewMat * projMat);

	XMStoreFloat4x4(&m_ConstBuf.data.worldViewProjMatrix, mvpMat);
	XMStoreFloat4x4(&m_ConstBuf.data.worldMatrix, worldTransMat);
	//cModelManager::Load("Link.x");
	// =============================================
}

void cRenderingFramework::Draw(std::shared_ptr<cCommandSystem> m_CommandSystem, int frameIndex)
{
	auto commandSystemLists = m_CommandSystem->GetGameCommand();
	cRenderingOrder m_Order;
	for (int i = 0; i < 4; i++) {
		auto commandList = commandSystemLists[i].GetList(frameIndex);
		auto commandAlloc = commandSystemLists[i].GetAllocator(frameIndex);
		CheckHR(commandList->Reset(commandAlloc.Get(), nullptr));

		commandList->OMSetRenderTargets(1, &cDXWindow::GetBuuferData().descHandleRtv, true, &cDXWindow::GetBuuferData().descHandleDsv);


		// TODO ローカルで保存せずにグローバルで取得できるようにする
		D3D12_VIEWPORT viewport = {};
		viewport.Width = (float)1920;
		viewport.Height = (float)1080;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		commandList->RSSetViewports(1, &viewport);
		D3D12_RECT scissor = {};
		scissor.right = (LONG)1920;
		scissor.bottom = (LONG)1080;
		commandList->RSSetScissorRects(1, &scissor);

		// TODO 描画コンポーネントから使用するPSOを識別して変更する
		auto pso = m_PsoManager->RequestPSO("Main");
		commandList->SetGraphicsRootSignature(pso->GetSettingRootSignature()->GetRootSignature().Get());
		commandList->SetPipelineState(pso->GetPipelineState().Get());

		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		if (i == 1) {
			m_ConstBuf.Upload();
			DirectX::XMFLOAT4X4 mats[Render::g_MaxInstNum];
			m_Order.RetrunWorldMatrix(mats, frameIndex);
			auto cbvSrvUavDescHeap = m_ConstBuf.GetDescriptorHeap(frameIndex)->GetGPUDescriptorHandleForHeapStart();
			ID3D12DescriptorHeap* descHeaps[] = { m_ConstBuf.GetDescriptorHeap(frameIndex) };
			commandList->SetDescriptorHeaps(ARRAYSIZE(descHeaps), descHeaps);
			commandList->SetGraphicsRootDescriptorTable(0, cbvSrvUavDescHeap);
			cModelManager manager;
			manager.Draw(frameIndex,mats, 0, commandList.Get(), true, 1, 1);		// TODO 仮実装
		}

		commandList->Close();
	}
	m_Order.ClearObjs(frameIndex);
}

void cRenderingFramework::Execute(std::shared_ptr<cCommandSystem> m_CommandSystem, std::shared_ptr<cCommandQueue> queue, int frameIndex)
{
	auto commandSystemLists = m_CommandSystem->GetGameCommand();

	ID3D12CommandList* list[Render::g_ThreadNum] = {};

	for (int i = 0; i < Render::g_ThreadNum; i++) {
		list[i] = commandSystemLists[i].GetList(frameIndex).Get();
	}

	queue->Exe(list, Render::g_ThreadNum);
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
