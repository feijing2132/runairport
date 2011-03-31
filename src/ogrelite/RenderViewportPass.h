#pragma once
#include <OgrePrerequisites.h>
/*the object represent a render pass to the viewport
*/
namespace Ogre
{


class RendererProcess
{
public:
	virtual void doJob()=0;
	virtual ~RendererProcess(){}
	String sDesc;
};

// a group of render pass of the viewport
class RendererProcessSquence : public RendererProcess
{
public:	
	//bool m_bParalle; //no effect yet

	virtual void doJob();
	typedef std::vector<RendererProcess*> SquenceList;
	SquenceList mCompositions;
	

};

//the method class the represent how to render a frame and swap to show
class RenderOneFrameMethod
{
public:
	RenderOneFrameMethod():mRenderJob(NULL){}
	RendererProcess* mRenderJob;

	void Do()
	{
		if(mRenderJob)
		{
			mRenderJob->doJob();
		}
	}
	//
	void Load();//read from xml script
	void Save();//save to xml script

public://signal
	

};


}