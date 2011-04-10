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
class RenderCanvas;
class RenderProcess;
class RenderViewport 
{
public:
	RenderViewport() 
		:mpRenerProcess(NULL)
		,mbVisible(true)
	{
	}
	virtual void renderTo(RenderCanvas* pCanvas);
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
class RenderEngine;
class RenderCanvas
{
public:	
	virtual uint32 getWidth()const{ return mWidth; }
	virtual uint32 getHeigth()const{ return mHeight; }

	virtual RenderEngine* getSystem()=0;

	void renderOneFrame();
protected:
	virtual void _beginFrame()=0;
	virtual void _beginViewport(RenderViewport*player)=0;	
	virtual void _endFrame()=0;
protected:
	typedef std::list< RenderViewportSharedPtr > RenderLayerList;
	RenderLayerList mRenderLayList;
	uint32 mWidth;
	uint32 mHeight;

};
typedef nodelete_shared_ptr<RenderCanvas> RenderCanvasSharedPtr;
//////////////////////////////////////////////////////////////////////////


//only manage create/destroy resource
class Texture
{
public:

};
typedef nodelete_shared_ptr<Texture> TextureSharedPtr;





END_NAMESPACE_OGRELITE