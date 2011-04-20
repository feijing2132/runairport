#include "RenderProcess.h"

BEGIN_NAMESPACE_OGRELITE
void RenderProcessSquence::render()
{
	preRenderSeq();
	processRenderSeq();
	postRenderSeq();
}

void RenderProcessSquence::processRenderSeq()
{
	for(SequenceProcessList::iterator itr= mSequenceProcesses.begin();itr!=mSequenceProcesses.end();++itr)
	{
		(*itr)->render();
	}	
}

END_NAMESPACE_OGRELITE