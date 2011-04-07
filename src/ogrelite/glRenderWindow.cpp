#include "glRenderWindow.h"
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




void Win32GLRenderWindowCanvas::create( const String& name, unsigned int width, unsigned int height, const NameValueMap* miscParams )
{
	destory();
	if(miscParams)
	{
		int extWnd=0;
		if (miscParams->get("externalWindowHandle",extWnd))
		{
			mHWnd = (HWND)extWnd;		
		}
	}
	
	//get parameters from the 
	RECT rc;
	// top and left represent outer window position
	GetWindowRect(mHWnd, &rc);
	//mTop = rc.top;
	//mLeft = rc.left;
	// width and height represent drawable area only
	GetClientRect(mHWnd, &rc);
	//mWidth = rc.right;
	//mHeight = rc.bottom;

	mHDC = GetDC(mHWnd);
	int testFsaa = mFSAA;
	bool testHwGamma = hwGamma;
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
	mHwGamma = testHwGamma;
	mFSAA = testFsaa;
	


}
END_NAMESPACE_OGRELITE