#pragma once
#include "CommandSystem.h"
#include "CommandQueue.h"
#include "PSOManager.h"
// ↓消す
#include "ConstantBuffer.h"
#include "DXMath.h"

struct CBuffer {
	DirectX::XMFLOAT4X4 worldViewProjMatrix;
	DirectX::XMFLOAT4X4 worldMatrix;
};

/// <summary>
/// ゲームオブジェクトの描画を担当する描画の最も要となるクラス
/// </summary>
class cRenderingFramework
{
public:
	cRenderingFramework();
	~cRenderingFramework() = default;

	void Draw(std::shared_ptr<cCommandSystem> m_CommandSystem,int frameIndex);		// コマンド発行
	void Execute(std::shared_ptr<cCommandSystem> m_CommandSystem, std::shared_ptr<cCommandQueue> queue, int frameIndex);					// コマンド実行
private:
	void CreatePSO();		// この中でプログラム中で必要なPSOを作成する
	std::unique_ptr<cPSOManager> m_PsoManager;
	cConstBuf<CBuffer> m_ConstBuf;
};