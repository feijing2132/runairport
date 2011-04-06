#pragma once

#include "RenderViewportPass.h"
#include "OgreGLRenderSystem.h"

BEGIN_NAMESPACE_OGRELITE


	


class GLRenderWindow : public RenderWindow
{
public:
	virtual GLContext* getContext()=0;
	
};

#include <windows.h>
class Win32GLRenderWindow :public GLRenderWindow
{
public:
	HWND hWnd;
};

END_NAMESPACE_OGRELITE