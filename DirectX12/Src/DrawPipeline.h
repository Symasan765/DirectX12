#pragma once
#include "CommandQueue.h"
#include "SwapChain.h"

class cDrawPipeline
{
public:
	friend class cGameSystem;
	cDrawPipeline();
	~cDrawPipeline() = default;

private:
	std::unique_ptr<cCommandQueue> m_Queue;
};