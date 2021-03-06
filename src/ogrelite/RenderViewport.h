#pragma once
#include "ogrelitePrefix.h"
#include "../core/s_ptr.h"
#include "OgreColourValue.h"
#include "OgreCommon.h"


BEGIN_NAMESPACE_OGRELITE
///virtual base class represent a render operation to  
//class 
class RenderViewport;
//viewport layer to canvas 
class IRenderCanvas;
class IRenderProcess;
class RenderViewport 
{
public:
	RenderViewport() 
		:mpRenerProcess(NULL)
		,mbShow(true)
	{
	}
	virtual void renderTo(IRenderCanvas* pCanvas);
	bool isShow()const{ return mbShow; }
	void show(bool b){ mbShow = b; }	
	// Actual dimensions, based on target dimensions
	int mActLeft, mActTop, mActWidth, mActHeight;	
protected:	
	IRenderProcess* mpRenerProcess;		
	/// Viewport orientation
	int mOrientation;
	/// Background options
	bool mbShow;
};


typedef ref_ptr<RenderViewport> RenderViewportSharedPtr;

//render target
// window support or software support(FBO) which have , have buffers like pixel buffer , stencil buffer, depth buffer..

class BackGround
{
public:
	enum Type
	{
		_NONE,   //
		_SINGLE_COLOR, //
		_
	};
};

class IRenderEngine;
class IRenderCanvas
{
public:	
	virtual void getSize(uint32& width, uint32& height)const=0;	
	virtual IRenderEngine* getSystem()=0;
	virtual ~IRenderCanvas(){}

	void renderOneFrame();
protected:
	virtual void _beginFrame()=0;	
	virtual void _beginViewport(RenderViewport* pVp)=0;
	virtual void _endFrame()=0;
protected:
	typedef std::list< RenderViewportSharedPtr > RenderLayerList;
	RenderLayerList mRenderLayList;
};
typedef ref_ptr<IRenderCanvas> IRenderCanvasSharedPtr;
//////////////////////////////////////////////////////////////////////////


//only manage create/destroy resource
class Texture
{
public:

};
typedef ref_ptr<Texture> TextureSharedPtr;





END_NAMESPACE_OGRELITE