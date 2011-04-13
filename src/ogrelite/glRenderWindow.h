#pragma once

#include "RenderViewport.h"
#include "RenderEngine.h"


BEGIN_NAMESPACE_OGRELITE

	class IGLRenderCanvas : public IRenderCanvas
	{
	public:
		virtual void setCurrent()=0;
		virtual void endCurrent()=0;
		virtual void resize(int width, int height)=0;

	protected:
		virtual void _beginFrame(){ setCurrent(); }
		virtual void _beginViewport(RenderViewport* pVp);
		virtual void _endFrame(){ endCurrent(); }

	};
	//the window canvas usually the main canvas
	class GLRenderWindowCanvas : public IGLRenderCanvas
	{
	public:	
	};	
	
	class Win32GLRenderWindowCanvas;


END_NAMESPACE_OGRELITE