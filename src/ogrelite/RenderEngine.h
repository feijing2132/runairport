#pragma once
#include "ogrelitePrefix.h"
#include "RenderViewport.h"
#include "ogreliteptr.h"
#include "OgreWin32Context.h"

BEGIN_NAMESPACE_OGRELITE

class RenderEngine
{
public:
	//texture manager
	TextureSharedPtr createTexture(const String& sName,const NameValueMap* miscParams=NULL);
	void destoryTexture(const String& sName,bool bForce = false);
	TextureSharedPtr getTexture(const String& sName);
	std::map<String, inst_ptr<Texture> > mTextureMap;

	//the sub canvas from the prime	
	RenderCanvasSharedPtr createRenderCanvas(const String &name,const NameValueMap* miscParams=NULL );
	void destroyCanvas(const String& sName,bool bForce = false);
	RenderCanvasSharedPtr getRenderCanvas(const String& sName){ return mCanvasMap[sName];}

	std::map<String, inst_ptr<RenderCanvas> > mCanvasMap;	
	//
protected:
	//internal create functions 
	virtual RenderCanvas* _createCanvasImpl(const String &name,const NameValueMap* miscParams=NULL )=0;
	virtual Texture* _createTextureImpl(const String &name,const NameValueMap* miscParams=NULL )=0;

};

class GLRenderEngine : public RenderEngine
{
public:
	GLSupport* getGLSupport(){ return mpGLSupport.get(); }
	GLRenderEngine();
protected:
	inst_ptr<GLSupport> mpGLSupport;
	virtual RenderCanvas* _createCanvasImpl(const String &name,const NameValueMap* miscParams=NULL );
	virtual Texture* _createTextureImpl(const String &name,const NameValueMap* miscParams=NULL );

};
END_NAMESPACE_OGRELITE