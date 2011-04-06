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


void RenderCanvas::renderOneFrame()
{
	//sort visible layers
	typedef std::list<RenderLayerSharePtr> RenderLayerVector;
	RenderLayerVector sortedLayers;
	for(RenderLayerMap::iterator itr=mLayerInstMap.begin();itr!=mLayerInstMap.end();++itr)
	{
		inst_ptr<RenderLayer>& layer = itr->second;
		if(layer.isValid() && layer->isVisible() )
		{
			RenderLayerVector::iterator itrInsertPos = sortedLayers.begin();
			for(;itrInsertPos!=sortedLayers.end();++itrInsertPos)
			{
				if( (*itrInsertPos)->getOrder() < layer->getOrder())
				{					
					break;
				}
			}
			sortedLayers.insert(itrInsertPos,layer);
		}
	}
	//draw each visible layers to canvas
	for(RenderLayerVector::iterator itr=sortedLayers.begin();itr!=sortedLayers.end();++itr)
	{
		RenderLayerSharePtr& shptr=*itr;
		shptr->drawToCanvas(this);
	}
	//
}



RenderLayer::RenderLayer() 
	:mpRenerer(NULL)
{

}

END_NAMESPACE_OGRELITE