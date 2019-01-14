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
	// TODO スレッドごとに利用する関数を作成してマルチスレッド化させる
	for (int i = 0; i < 4; i++) {
		auto commandList = commandSystemLists[i].GetList(frameIndex);
		auto commandAlloc = commandSystemLists[i].GetAllocator(frameIndex);
		
		if (i == 1) {
			OpaquePass(commandList, commandAlloc, frameIndex);
		}
		else {
			CheckHR(commandList->Reset(commandAlloc.Get(), nullptr));
			commandList->Close();
		}
	}
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

void cRenderingFramework::OpaquePass(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList, Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAlloc, int frameIndex)
{
	CheckHR(commandList->Reset(commandAlloc.Get(), nullptr));

	commandList->OMSetRenderTargets(1, &cDXWindow::GetBuuferData().descHandleRtv, true, &cDXWindow::GetBuuferData().descHandleDsv);
	cRenderingOrder m_Order;

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

	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_ConstBuf.Upload();
	DirectX::XMFLOAT4X4 mats[Render::g_MaxInstNum];
	auto& renderingObj = m_Order.GetMapObj();	// 描画するオブジェクト
	std::string NowPsoName = "";
	cModelManager manager;

	// 登録されているリソースオブジェクトをすべて更新する
	for (auto& itr : renderingObj) {
		// PSOが登録されているかチェック
		if (NowPsoName != itr.second[0]->GetPsoName()) {
			// PSOを新しく登録
			auto pso = m_PsoManager->RequestPSO(itr.second[0]->GetPsoName());
			commandList->SetGraphicsRootSignature(pso->GetSettingRootSignature()->GetRootSignature().Get());
			commandList->SetPipelineState(pso->GetPipelineState().Get());
		}

		auto cbvSrvUavDescHeap = m_ConstBuf.GetDescriptorHeap(frameIndex)->GetGPUDescriptorHandleForHeapStart();
		ID3D12DescriptorHeap* descHeaps[] = { m_ConstBuf.GetDescriptorHeap(frameIndex) };
		commandList->SetDescriptorHeaps(ARRAYSIZE(descHeaps), descHeaps);
		commandList->SetGraphicsRootDescriptorTable(0, cbvSrvUavDescHeap);
		m_Order.RetrunWorldMatrix(itr.first, mats, frameIndex);
		manager.Draw(frameIndex, mats, itr.first, commandList.Get(), true, 1, itr.second.size());		// TODO 仮実装
	}

	commandList->Close();
}

void cRenderingFramework::CreatePSO()
{
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
		pso->CreatePipelineState(1);
	}

	{
		auto pso = m_PsoManager->RequestPSO("Sprite");
		auto rootSig = pso->GetSettingRootSignature();
		auto shaderByte = pso->GetSettingShaderByte();
		auto inputLayout = pso->GetSettingInputLayout();
		auto& format = pso->GetSettingRtvFormat();

		rootSig->AddSamplers(0);
		rootSig->AddSRV(0);

		shaderByte->CompileFromFile("HLSL/ScreenQuad.hlsl", "VSMain", "PSMain");

		inputLayout->AddElement<DirectX::XMFLOAT3>("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
		inputLayout->AddElement<DirectX::XMFLOAT2>("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);

		format.push_back(DXGI_FORMAT_R8G8B8A8_UNORM);
		pso->CreatePipelineState(10);
	}
}
