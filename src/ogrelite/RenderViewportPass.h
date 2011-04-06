#pragma once
#include "ogrelitePrefix.h"
#include "ogreliteptr.h"
/*the object represent a render pass to the viewport
*/

BEGIN_NAMESPACE_OGRELITE
///virtual base class represent a render operation to 
class RenderProcess
{
public:
	virtual void process()=0;
	virtual ~RenderProcess(){}
protected:
	String sDesc;
};

// a group of render process
class RenderProcessSquence : public RenderProcess
{
protected:	
	//bool m_bParalle; //no effect yet
	void process();
	virtual void preProcessSeq(){}
	virtual void postProcessSeq(){}
protected:
	typedef std::vector<RenderProcess*> SequenceProcessList;
	SequenceProcessList mSequenceProcesses;
	void processSeq();
};

//viewport layer to canvas 
class RenderCanvas;
class RenderLayer 
{
public:
	RenderLayer() 
		:mpRenerProcess(NULL)
		,mbVisible(true)
	{
	}
	virtual void drawToCanvas(RenderCanvas* pCanvas);
	bool isVisible()const{ return mbVisible; }
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
	/// ZOrder	
	bool mbVisible;
};


typedef shared_ptr<RenderLayer> RenderLayerSharePtr;

//render target
// window support or software support(FBO) which have , have buffers like pixel buffer , stencil buffer, depth buffer..
class RenderSystem;
class RenderCanvas
{
public:	
	void renderOneFrame();

	virtual void beginFrame()=0;
	
	virtual void endFrame()=0;
	virtual uint32 getWidth()const=0;
	virtual uint32 getHeigth()const=0;

	virtual RenderSystem* getSystem()=0;

protected:
	typedef std::list< RenderLayerSharePtr > RenderLayerList;
	RenderLayerList mRenderLayList;

};

//only manage create/destroy resource
class Texture
{
public:

};
typedef shared_ptr<Texture> TextureSharePtr;

class RenderSystem
{
public:
	//texture manager
	TextureSharePtr createTexture(const String& sName);
	void destoryTexture(const String& sName,bool bForce = false);
	TextureSharePtr getTexture(const String& sName);
	HashMap<String, inst_ptr<Texture> > mTextureMap;
	//


};



END_NAMESPACE_OGRELITE