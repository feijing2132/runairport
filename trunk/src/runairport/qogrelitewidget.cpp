#include "StdAfx.h"
#include "qogrelitewidget.h"

#include "../ogrelite/glRenderWindow.h"

using namespace Ogre;
using namespace OgreLite;
//////////////////////////////////////////////////////////////////////////
static String sMainCanvas = ("MainCanvas"); 


BEGIN_NAMESPACE_OGRELITE


class QTGLRenderEngine;
class QTGLWindowCanvase : public IGLRenderCanvas
{
public:
	QTGLWindowCanvase(QGLWidget* pGlWidget, QTGLRenderEngine* pEngine)
	{ 
		mpEngine = pEngine; 
		mpWidget = pGlWidget;
	}
	IRenderEngine* getSystem();
	virtual void setCurrent(){	mpWidget->makeCurrent();}
	virtual void endCurrent(){ 	}

	virtual uint32 getWidth()const{ return mpWidget->size().width(); }
	virtual uint32 getHeight()const{ return mpWidget->size().height();  };
	virtual void resize(int width, int height){  }

protected:
	QTGLRenderEngine* mpEngine;
	QGLWidget* mpWidget;
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
	virtual Texture* _createTextureImpl(const String &name,const NameValueMap* miscParams/* =NULL */)
	{
		return NULL;
	}
};

IRenderEngine* QTGLWindowCanvase::getSystem()
{
	return mpEngine;
}
END_NAMESPACE_OGRELITE

using namespace OgreLite;
//////////////////////////////////////////////////////////////////////////
QOgreLiteWidget::QOgreLiteWidget(QWidget *parent)
	: QGLWidget(parent)
{	
	startTimer(1);
	mpEngine= new QTGLRenderEngine();
	NameValueMap paremeters;
	paremeters.set("QGLWidget", (int)this);
	mpEngine->createRenderCanvas(sMainCanvas,&paremeters);	
}

QOgreLiteWidget::~QOgreLiteWidget()
{

}



void QOgreLiteWidget::timerEvent( QTimerEvent* evt )
{
	Q_UNUSED(evt);
	update();
}

void QOgreLiteWidget::paintGL()
{
	IRenderCanvasSharedPtr thisCanvas = mpEngine->getRenderCanvas(sMainCanvas);
	if(thisCanvas.get())
	{
		thisCanvas->renderOneFrame();
	}
}



void QOgreLiteWidget::resizeGL( int w, int h )
{
	
}

void QOgreLiteWidget::initializeGL()
{	
}

