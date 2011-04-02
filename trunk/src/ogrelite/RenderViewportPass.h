#pragma once
#include "ogrelitePrefix.h"
/*the object represent a render pass to the viewport
*/

BEGIN_NAMESPACE_OGRELITE
///virtual base class represent a render operation to 
class RenderProcess
{
public:
	virtual void process()=0;
	virtual ~RenderProcess(){}
protected:
	String sDesc;
};

// a group of render process
class RenderProcessSquence : public RenderProcess
{
protected:	
	//bool m_bParalle; //no effect yet
	void process();
	virtual void preProcessSeq(){}
	virtual void postProcessSeq(){}
protected:
	typedef std::vector<RenderProcess*> SequenceProcessList;
	SequenceProcessList mSequenceProcesses;
	void processSeq();
};

//viewport layer to canvas 
class RenderCanvas;
class RenderLayer 
{
public:
	virtual void drawToCanvas(RenderCanvas* pCanvas);
protected:	
	RenderProcess* mpRenerer;	
	//int mActLeft, mActTop, mActWidth, mActHeight;
	/// ZOrder
	int mZOrder;
};
//render target
// window support or software support(FBO) which have , have buffers like pixel buffer , stencil buffer, depth buffer..
class RenderCanvas
{
public:

	void resize();
protected:
	unsigned int mWidth;
	unsigned int mHeight;
};

class RenderWindow  : public RenderCanvas
{
public:
	
}

END_NAMESPACE_OGRELITE