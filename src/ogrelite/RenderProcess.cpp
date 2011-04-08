#include "RenderProcess.h"

BEGIN_NAMESPACE_OGRELITE
void RenderProcessSquence::render(RenderViewport* pdest)
{
	preRenderSeq();
	processRenderSeq(pdest);
	postRenderSeq();
}

void RenderProcessSquence::processRenderSeq( RenderViewport* pdest )
{
	for(SequenceProcessList::iterator itr= mSequenceProcesses.begin();itr!=mSequenceProcesses.end();++itr)
	{
		(*itr)->render(pdest);
	}	
}

END_NAMESPACE_OGRELITE