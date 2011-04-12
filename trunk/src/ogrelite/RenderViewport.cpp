#include "RenderViewport.h"
#include "RenderProcess.h"

BEGIN_NAMESPACE_OGRELITE
//////////////////////////////////////////////////////////////////////////
void IRenderCanvas::renderOneFrame()
{
	_beginFrame();
	//render each layer
	for(RenderLayerList::iterator itr=mRenderLayList.begin();itr!=mRenderLayList.end();++itr)
	{
		RenderViewportSharedPtr& shptr=*itr;
		if(shptr.get() && shptr->isVisible() )
		{			
			_beginViewport(shptr.get());
			shptr->renderTo(this);
		}
	}
	_endFrame();
}





void RenderViewport::renderTo( IRenderCanvas* pCanvas )
{
	if(mpRenerProcess)
		mpRenerProcess->render(this);
}

END_NAMESPACE_OGRELITE