#pragma once
#include "ogrelitePrefix.h"
#include "ogreliteptr.h"

BEGIN_NAMESPACE_OGRELITE
	///virtual base class represent a render operation to  
	//class 
class IRenderEngine;
class IRenderProcess
{
public:
	virtual void render()=0;
	virtual ~IRenderProcess(){}
protected:
	String sDesc;
};

// a group of render process
class RenderProcessSquence : public IRenderProcess
{
protected:	
	//bool m_bParalle; //no effect yet
	void render();
	virtual void preRenderSeq(){}
	virtual void postRenderSeq(){}
protected:
	typedef std::vector<IRenderProcess*> SequenceProcessList;
	SequenceProcessList mSequenceProcesses;
	void processRenderSeq();
};

END_NAMESPACE_OGRELITE