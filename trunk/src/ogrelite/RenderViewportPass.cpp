#include "RenderViewportPass.h"

BEGIN_NAMESPACE_OGRELITE

void RenderProcessSquence::doJob()
{	
	for(SquenceList::iterator itr= mCompositions.begin();itr!=mCompositions.end();++itr)
	{
		(*itr)->doRender();
	}	
}


END_NAMESPACE_OGRELITE