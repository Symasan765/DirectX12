#pragma once
#include "CommandQueue.h"
#include "SwapChain.h"
#include "CommandSystem.h"
#include "FenceObj.h"
#include "ResourceBarrier.h"
#include "RenderingFramework.h"

class cDrawPipeline
{
public:
	friend class cGameSystem;

	void ProcessingCPU(int frameIndex);		// コマンドの発行
	void ProcessingGPU(int frameIndex);		// コマンドの実行
private:
	cDrawPipeline();
	~cDrawPipeline();
	void DrawBigen(int frameIndex);
	void DrawGame(int frameIndex);
	void DrawImGUI(int frameIndex);
	void DrawEnd(int frameIndex);

	void ExeBigen(int frameIndex);
	void ExeGame(int frameIndex);
	void ExeImGUI(int frameIndex);
	void ExeEnd(int frameIndex);

	std::shared_ptr<cCommandQueue> m_Queue;
	std::shared_ptr<cCommandSystem> m_CommandSystem;
	std::unique_ptr<cFenceObj> m_FenceObj;
	std::unique_ptr<cResourceBarrier> m_RtvResourceBarrier;
	std::unique_ptr<cRenderingFramework> m_RenderingFramework;
};