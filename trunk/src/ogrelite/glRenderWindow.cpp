#include "glRenderWindow.h"
#include "OgreWin32GLSupport.h"
#include "OgreException.h"
#include <OgreStringConverter.h>


BEGIN_NAMESPACE_OGRELITE


void Win32GLRenderWindowCanvas::swapBuffers( bool waitForVSync )
{
	SwapBuffers( mHDC );
}

void Win32GLRenderWindowCanvas::destory()
{
	if (!mHWnd)
		return;
	// Unregister and  destroyOGRE GLContext	
	mContext = NULL;	
	// just release the DC
	ReleaseDC(mHWnd, mHDC);
	
	mHDC = 0; // no release thanks to CS_OWNDC wndclass style
	mHWnd = 0;
}






void Win32GLRenderWindowCanvas::create( const String& name,const NameValueMap* miscParams/*=NULL*/ )
{
	destory();
	if(miscParams)
	{
		String sWnd;
		if (miscParams->get("externalWindowHandle",sWnd))
		{
			mHWnd = (HWND) StringConverter::parseInt(sWnd);		
		}
	}
	if(!mHWnd)
		return;
	//get parameters from the 
	RECT rc;
	// top and left represent outer window position
	GetWindowRect(mHWnd, &rc);
	//mTop = rc.top;
	//mLeft = rc.left;
	// width and height represent drawable area only
	GetClientRect(mHWnd, &rc);
	mWidth = rc.right;
	mHeight = rc.bottom;

	//create dc
	mHDC = GetDC(mHWnd);

	Win32GLSupport& mGLSupport = (Win32GLSupport&)(*mpRenderEngine->getGLSupport());
	int testFsaa = 0;
	bool testHwGamma = 0;
	int mColourDepth = 32;
	int mFSAA = 0;
	int hwGamma = 0;

	bool formatOk = mGLSupport.selectPixelFormat(mHDC, mColourDepth, testFsaa, testHwGamma);
	if (!formatOk)
	{
		if (mFSAA > 0)
		{
			// try without FSAA
			testFsaa = 0;
			formatOk = mGLSupport.selectPixelFormat(mHDC, mColourDepth, testFsaa, testHwGamma);
		}

		if (!formatOk && hwGamma)
		{
			// try without sRGB
			testHwGamma = false;
			testFsaa = mFSAA;
			formatOk = mGLSupport.selectPixelFormat(mHDC, mColourDepth, testFsaa, testHwGamma);
		}

		if (!formatOk && hwGamma && (mFSAA > 0))
		{
			// try without both
			testHwGamma = false;
			testFsaa = 0;
			formatOk = mGLSupport.selectPixelFormat(mHDC, mColourDepth, testFsaa, testHwGamma);
		}

		if (!formatOk)
			OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR, 
			"selectPixelFormat failed", "Win32Window::create");

	}
	// record what gamma option we used in the end
	// this will control enabling of sRGB state flags when used
	//mHwGamma = testHwGamma;
	//mFSAA = testFsaa;
	HGLRC mGlrc = wglCreateContext(mHDC);
	if (!mGlrc)
		OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR, 
		"wglCreateContext failed: " + translateWGLError(), "Win32Window::create");

	if(GLRenderCanvas* pInitCanvas = mGLSupport.getInitCanvas())
	{
		pInitCanvas->getGLContext()->setCurrent();	
		HGLRC old_context = wglGetCurrentContext();
		if (!wglShareLists(old_context, mGlrc))
			OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR, "wglShareLists() failed", " Win32Window::create");
	}

	mContext = new Win32Context(mHDC, mGlrc);
}
END_NAMESPACE_OGRELITE