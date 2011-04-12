#pragma once

#include "RenderViewport.h"
#include "RenderEngine.h"


BEGIN_NAMESPACE_OGRELITE

	class IGLRenderCanvas : public IRenderCanvas
	{
	public:
		virtual void setCurrent()=0;
		virtual void endCurrent()=0;

	};
	//the window canvas usually the main canvas
	class GLRenderWindowCanvas : public IGLRenderCanvas
	{
	public:	
	};	
	
	class Win32GLRenderWindowCanvas;


END_NAMESPACE_OGRELITE