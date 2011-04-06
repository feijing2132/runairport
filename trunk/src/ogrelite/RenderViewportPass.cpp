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


//////////////////////////////////////////////////////////////////////////
void RenderCanvas::renderOneFrame()
{
	beginFrame();
	//render each layer
	for(RenderLayerList::iterator itr=mRenderLayList.begin();itr!=mRenderLayList.end();++itr)
	{
		RenderLayerSharePtr& shptr=*itr;
		if(shptr.get() && shptr->isVisible() )
		{			
			shptr->drawToCanvas(this);
		}
	}
	endFrame();
}





void RenderLayer::drawToCanvas( RenderCanvas* pCanvas )
{
		

	if(mpRenerProcess)
		mpRenerProcess->process();

}

END_NAMESPACE_OGRELITE