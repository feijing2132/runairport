#pragma once

#include "RenderViewport.h"
#include "RenderEngine.h"


BEGIN_NAMESPACE_OGRELITE

	class GLRenderCanvas : public RenderCanvas
	{
	public:		
		virtual RenderEngine* getSystem(){ return mpRenderEngine; }
		virtual void _beginFrame(){};
		virtual void _beginViewport(RenderViewport*player){};	
		virtual void _endFrame(){};

		virtual GLContext* getGLContext()=0;
	protected:
		GLRenderEngine* mpRenderEngine;
	};

	
	class Win32GLRenderWindowCanvas : public GLRenderCanvas
	{
	public:		
		Win32GLRenderWindowCanvas(GLRenderEngine* pEngine)
		{
			mpRenderEngine = pEngine;
		}
		void create(const String& name, const NameValueMap* miscParams=NULL);		

		HDC getHDC(){ return mHDC; }
		virtual GLContext* getGLContext(){ return mContext.get(); };
	protected:
		HWND mHWnd;
		HDC  mHDC; //own need to release 
		inst_ptr<Win32Context> mContext;

		void swapBuffers(bool waitForVSync);

		void destory();
	};

	


END_NAMESPACE_OGRELITE