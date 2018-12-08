#include "DrawPipeline.h"

cDrawPipeline::cDrawPipeline()
{
	m_Queue = std::make_unique<cCommandQueue>();
}
