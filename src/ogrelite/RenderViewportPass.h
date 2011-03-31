#pragma once
#include "ogrelitePrefix.h"
/*the object represent a render pass to the viewport
*/
BEGIN_NAMESPACE_OGRELITE
///virtual base class represent a render operation to 
class RenderProcess
{
public:
	void doRender()
	{
		begin();
		doJob();
		end();
	}

	virtual ~RenderProcess(){}
protected:
	virtual void doJob(){}
	virtual void begin(){}
	virtual void end(){}

	String sDesc;
};

// a group of render process
class RenderProcessSquence : public RenderProcess
{
protected:	
	//bool m_bParalle; //no effect yet
	virtual void doJob();

protected:
	typedef std::vector<RenderProcess*> SquenceList;
	SquenceList mCompositions;
};
//a render queue form ogre
class RenderQueue : public RenderProcess
{
public:

};


//a group of process render to one render target, switch context
class RenderTargetProcess : public RenderProcessSquence 
{
public:
	virtual void begin(){}
	virtual void end(){}
};

END_NAMESPACE_OGRELITE