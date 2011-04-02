#include "RenderViewportPass.h"

BEGIN_NAMESPACE_OGRELITE

void RenderProcessSquence::processSeq()
{	
	for(SequenceProcessList::iterator itr= mSequenceProcesses.begin();itr!=mSequenceProcesses.end();++itr)
	{
		(*itr)->process();
	}	
}

void RenderProcessSquence::process()
{
	preProcessSeq();
	processSeq();
	postProcessSeq();
}

END_NAMESPACE_OGRELITE