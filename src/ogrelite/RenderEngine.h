#pragma once
#include "ogrelitePrefix.h"
#include "RenderViewport.h"
#include "ogreliteptr.h"


BEGIN_NAMESPACE_OGRELITE

class IRenderEngine
{
public:
	virtual ~IRenderEngine(){}
	//texture manager
	TextureSharedPtr createTexture(const String& sName,const NameValueMap* miscParams=NULL);
	void destoryTexture(const String& sName,bool bForce = false);
	TextureSharedPtr getTexture(const String& sName);
	std::map<String, inst_ptr<Texture> > mTextureMap;

	//the sub canvas from the prime	
	IRenderCanvasSharedPtr createRenderCanvas(const String &name,const NameValueMap* miscParams=NULL );
	void destroyCanvas(const String& sName,bool bForce = false);
	IRenderCanvasSharedPtr getRenderCanvas(const String& sName){ return mCanvasMap[sName];}

	std::map<String, inst_ptr<IRenderCanvas> > mCanvasMap;	
	//
protected:
	virtual IRenderCanvas* _createCanvasImpl(const String& sName,const NameValueMap* miscParams=NULL)=0;
	virtual Texture* _createTextureImpl(const String &name,const NameValueMap* miscParams=NULL)=0;
};


END_NAMESPACE_OGRELITE