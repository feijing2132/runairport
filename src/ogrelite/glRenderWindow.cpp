#include "glRenderWindow.h"
#include "OgreException.h"
#include <OgreStringConverter.h>
#include "OgreGLPrerequisites.h"

BEGIN_NAMESPACE_OGRELITE

//platform engine canvas


//
void IGLRenderCanvas::_beginViewport( RenderViewport* pVp )
{
	glViewport(pVp->mActTop,pVp->mActLeft,pVp->mActWidth,pVp->mActHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
END_NAMESPACE_OGRELITE