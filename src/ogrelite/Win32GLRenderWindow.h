#pragma once
#include "../core/s_ptr.h"
#include "OgreWin32Context.h"
#include "OgreWin32GLSupport.h"

BEGIN_NAMESPACE_OGRELITE
class Win32GLRenderEngine : public IRenderEngine
{
public:
	inst_ptr<Win32GLSupport> m_pGLSupport;
};

class Win32GLRenderWindowCanvas : public GLRenderWindowCanvas
{
public:		
	Win32GLRenderWindowCanvas(Win32GLRenderEngine* pEngine)
	{
		mpRenderEngine = pEngine;
	}
	void create(const String& name, const NameValueMap* miscParams=NULL);
	HDC getHDC(){ return mHDC; }	

	virtual void _beginFrame();	
	virtual void _endFrame();
	virtual void setCurrent();
	virtual void endCurrent();
	virtual void getSize(uint32& width, uint32& height)const;
	virtual IRenderEngine* getSystem();

protected:
	HWND mHWnd;
	HDC  mHDC; //own need to release 
	Win32GLRenderEngine* mpRenderEngine;

	inst_ptr<Win32Context> mContext;

	void swapBuffers(bool waitForVSync);

	void destory();
};
END_NAMESPACE_OGRELITE