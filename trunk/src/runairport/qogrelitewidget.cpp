#include "StdAfx.h"
#include "qogrelitewidget.h"

#include "../ogrelite/glRenderWindow.h"

using namespace Ogre;
using namespace OgreLite;
//////////////////////////////////////////////////////////////////////////
static String mainCanvas = ("MainCanvas"); 


BEGIN_NAMESPACE_OGRELITE


class QTGLRenderEngine;
class QTGLWindowCanvase : public IGLRenderCanvas
{
public:
	QTGLWindowCanvase(QGLWidget* pGlWidget, QTGLRenderEngine* pEngine)
	{ 
		mpEngine = pEngine; 
	}
	IRenderEngine* getSystem();
protected:
	QTGLRenderEngine* mpEngine;
};


class QTGLRenderEngine : public IRenderEngine
{
public:

protected:
	virtual IRenderCanvas* _createCanvasImpl(const String& sName,const NameValueMap* miscParams=NULL)
	{
		int widgetPtr = NULL;
		if(miscParams->get("QGLWidget",widgetPtr))
		{
			return new QTGLWindowCanvase((QGLWidget*)widgetPtr,this);
		}
		return NULL;		
	}
};

IRenderEngine* QTGLWindowCanvase::getSystem()
{
	return mpEngine;
}
END_NAMESPACE_OGRELITE

//////////////////////////////////////////////////////////////////////////
QOgreLiteWidget::QOgreLiteWidget(QWidget *parent)
	: QGLWidget(parent)
{
	mbSetupOgre = false; 	
	startTimer(1);

}

QOgreLiteWidget::~QOgreLiteWidget()
{

}

void QOgreLiteWidget::paintEvent( QPaintEvent*evt )
{	
	if(!mbSetupOgre)
	{
		mbSetupOgre = true;
		SetupOgre();
	}
	if (updatesEnabled()) 
	{
		RenderCanvasSharedPtr pCanvas = d->pEngine.getRenderCanvas(mainCanvas);
		pCanvas->renderOneFrame();
	}
	
}

void QOgreLiteWidget::resizeEvent( QResizeEvent* )
{		
	update();
}


void QOgreLiteWidget::SetupOgre()
{

}

void QOgreLiteWidget::timerEvent( QTimerEvent* evt )
{
	Q_UNUSED(evt);
	update();
}

