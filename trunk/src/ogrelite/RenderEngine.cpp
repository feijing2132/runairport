#include "RenderEngine.h"

#include "OgreWin32GLSupport.h"
BEGIN_NAMESPACE_OGRELITE





GLRenderEngine::GLRenderEngine()
{
	mpGLSupport = new Win32GLSupport();
}

RenderCanvas* GLRenderEngine::_createCanvasImpl( const String &name,const NameValueMap* miscParams/*=NULL */ )
{
	return mpGLSupport->newRenderCanvas(name,this,miscParams);
}

Texture* GLRenderEngine::_createTextureImpl( const String &name,const NameValueMap* miscParams/*=NULL */ )
{
	return NULL;
}

RenderCanvasSharedPtr RenderEngine::createRenderCanvas( const String &name,const NameValueMap* miscParams/*=NULL */ )
{
	RenderCanvas* pCanavs = _createCanvasImpl(name,miscParams);
	if(pCanavs)
	{
		mCanvasMap[name] =  pCanavs;
	}
	return mCanvasMap[name];
}
END_NAMESPACE_OGRELITE