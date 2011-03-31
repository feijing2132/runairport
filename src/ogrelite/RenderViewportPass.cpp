#include "RenderViewportPass.h"



void Ogre::RendererProcessSquence::doJob()
{
	for(SquenceList::iterator itr= mCompositions.begin();itr!=mCompositions.end();++itr)
	{
		(*itr)->doJob();
	}
}
