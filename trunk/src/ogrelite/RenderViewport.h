#pragma once
#include "ogrelitePrefix.h"
#include "ogreliteptr.h"
#include "OgreColourValue.h"
#include "OgreCommon.h"


BEGIN_NAMESPACE_OGRELITE
///virtual base class represent a render operation to  
//class 
class RenderViewport;
//viewport layer to canvas 
class IRenderCanvas;
class RenderProcess;
class RenderViewport 
{
public:
	RenderViewport() 
		:mpRenerProcess(NULL)
		,mbVisible(true)
	{
	}
	virtual void renderTo(IRenderCanvas* pCanvas);
	bool isVisible()const{ return mbVisible; }
	void setVisible(bool b){ mbVisible = b; }
	void setClearEveryFrame( unsigned int buffers = FBT_COLOUR | FBT_DEPTH);
protected:	
	RenderProcess* mpRenerProcess;		
	// Actual dimensions, based on target dimensions
	int mActLeft, mActTop, mActWidth, mActHeight;	
	/// Viewport orientation
	int mOrientation;
	/// Background options
	ColourValue mClearColour;
	float mClearDepth;
	int mClearStencil;
	unsigned int mClearBuffers;	
	bool mbVisible;
};


typedef nodelete_shared_ptr<RenderViewport> RenderViewportSharedPtr;

//render target
// window support or software support(FBO) which have , have buffers like pixel buffer , stencil buffer, depth buffer..
class IRenderEngine;
class IRenderCanvas
{
public:	
	virtual uint32 getWidth()const=0;
	virtual uint32 getHeight()const=0;
	virtual IRenderEngine* getSystem()=0;

	void renderOneFrame();
protected:
	virtual void _beginFrame()=0;	
	virtual void _endFrame()=0;
protected:
	typedef std::list< RenderViewportSharedPtr > RenderLayerList;
	RenderLayerList mRenderLayList;
};
typedef nodelete_shared_ptr<IRenderCanvas> IRenderCanvasSharedPtr;
//////////////////////////////////////////////////////////////////////////


//only manage create/destroy resource
class Texture
{
public:

};
typedef nodelete_shared_ptr<Texture> TextureSharedPtr;





END_NAMESPACE_OGRELITE