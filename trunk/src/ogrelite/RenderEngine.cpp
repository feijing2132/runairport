#include "RenderEngine.h"

#include "OgreWin32GLSupport.h"
BEGIN_NAMESPACE_OGRELITE







RenderCanvasSharedPtr IRenderEngine::createRenderCanvas( const String &name,const NameValueMap* miscParams/*=NULL */ )
{
	IRenderCanvas* pCanavs = _createCanvasImpl(name,miscParams);
	if(pCanavs)
	{
		mCanvasMap[name] =  pCanavs;
		
	}
	return mCanvasMap[name];
}
END_NAMESPACE_OGRELITE