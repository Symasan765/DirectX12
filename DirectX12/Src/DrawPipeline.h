#pragma once
#include "CommandQueue.h"
#include "SwapChain.h"
#include "CommandSystem.h"

class cDrawPipeline
{
public:
	friend class cGameSystem;
	cDrawPipeline();
	~cDrawPipeline() = default;

private:
	std::unique_ptr<cCommandQueue> m_Queue;
	std::unique_ptr<cCommandSystem> m_CommandSystem;
};