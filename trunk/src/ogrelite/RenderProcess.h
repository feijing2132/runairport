#pragma once
#include "ogrelitePrefix.h"
#include "ogreliteptr.h"

BEGIN_NAMESPACE_OGRELITE
	///virtual base class represent a render operation to  
	//class 
class RenderViewport;
class RenderProcess
{
public:
	virtual void render(RenderViewport* pdest)=0;
	virtual ~RenderProcess(){}
protected:
	String sDesc;
};

// a group of render process
class RenderProcessSquence : public RenderProcess
{
protected:	
	//bool m_bParalle; //no effect yet
	void render(RenderViewport* pdest);
	virtual void preRenderSeq(){}
	virtual void postRenderSeq(){}
protected:
	typedef std::vector<RenderProcess*> SequenceProcessList;
	SequenceProcessList mSequenceProcesses;
	void processRenderSeq(RenderViewport* pdest);
};

END_NAMESPACE_OGRELITE