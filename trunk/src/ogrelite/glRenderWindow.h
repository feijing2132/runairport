#pragma once

#include "RenderViewportPass.h"
#include "RenderSystem.h"
#include "OgreWin32Context.h"

BEGIN_NAMESPACE_OGRELITE

	class GLRenderWindowCanvas : public RenderCanvas
	{
	public:

	};
	
	class Win32GLRenderWindowCanvas : public GLRenderWindowCanvas
	{
	public:				
		void create(const String& name, unsigned int width, unsigned int height,
			const NameValueMap* miscParams=NULL);
		Win32GLRenderWindowCanvas* clone(const String&name,const NameValueMap* miscParams=NULL);

	protected:
		
		HDC  mHDC; //own need to release 
		inst_ptr<Win32Context> mContext;

		void swapBuffers(bool waitForVSync);

		void destory();
	};

	class GLRenderSystem : public RenderSystem
	{
	public:
		
	};


END_NAMESPACE_OGRELITE