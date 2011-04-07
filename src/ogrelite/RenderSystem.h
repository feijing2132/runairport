#pragma once
#include "ogrelitePrefix.h"
#include "RenderViewportPass.h"
#include "ogreliteptr.h"

BEGIN_NAMESPACE_OGRELITE

class RenderSystem
{
public:
	//texture manager
	TextureSharedPtr createTexture(const String& sName,const NameValueMap* miscParams=NULL);
	void destoryTexture(const String& sName,bool bForce = false);
	TextureSharedPtr getTexture(const String& sName);
	HashMap<String, inst_ptr<Texture> > mTextureMap;

	//the sub canvas from the prime	
	RenderCanvasSharedPtr createRenderCanvas(const String &name,const NameValueMap* miscParams=NULL );
	void destroyCanvas(const String& sName,bool bForce = false);
	RenderCanvasSharedPtr getRenderCanvas(const String& sName);
	HashMap<String, inst_ptr<RenderCanvas> > mSubCanvasMap;
	//the main canvas usually a 
	RenderCanvasSharedPtr createPrimeCanvas(const NameValueMap* miscParams=NULL);
	RenderCanvasSharedPtr getPrimeCanvas(){ return mpPrimeCanvas; }
	inst_ptr<RenderCanvas> mpPrimeCanvas; 
	
	//
protected:
	//internal create functions 
	virtual RenderCanvas* _createCanvasImpl(const NameValueMap* miscParams=NULL)=0;
	virtual Texture* _createTextureImpl(const NameValueMap* miscParams=NULL)=0;

};


END_NAMESPACE_OGRELITE