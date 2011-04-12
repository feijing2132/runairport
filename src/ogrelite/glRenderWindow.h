#pragma once

#include "RenderViewport.h"
#include "RenderEngine.h"


BEGIN_NAMESPACE_OGRELITE

	class GLRenderCanvas : public RenderCanvas
	{
	public:		
		virtual RenderEngine* getSystem(){ return mpRenderEngine; }			
	protected:
		GLRenderEngine* mpRenderEngine;
	};
	//the window canvas usually the main canvas
	class GLRenderWindowCanvas : public GLRenderCanvas
	{
	public:
		virtual GLContext* getGLContext(){ return mContext.get(); };

	protected:
		inst_ptr<Win32Context> mContext;

		virtual void _beginFrame();
		virtual void _beginViewport(RenderViewport*player){}	
		virtual void _endFrame();
	};

	//platform canvas
	class Win32GLRenderWindowCanvas : public GLRenderWindowCanvas
	{
	public:		
		Win32GLRenderWindowCanvas(GLRenderEngine* pEngine)
		{
			mpRenderEngine = pEngine;
		}
		void create(const String& name, const NameValueMap* miscParams=NULL);
		HDC getHDC(){ return mHDC; }	

		virtual void _beginFrame();
		virtual void _endFrame();
	protected:
		HWND mHWnd;
		HDC  mHDC; //own need to release 
		

		void swapBuffers(bool waitForVSync);

		void destory();
	};

	


END_NAMESPACE_OGRELITE