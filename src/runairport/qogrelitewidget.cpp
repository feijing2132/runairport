#include "StdAfx.h"
#include "qogrelitewidget.h"
using namespace Ogre;
using namespace OgreLite;

static String mainCanvas = ("MainCanvas"); 

QOgreLiteWidget::QOgreLiteWidget(QWidget *parent)
	: QWidget(parent,0)
{
	mbSetupOgre = false;
}

QOgreLiteWidget::~QOgreLiteWidget()
{

}

void QOgreLiteWidget::paintEvent( QPaintEvent* )
{
	if(!mbSetupOgre)
	{
		mbSetupOgre = true;
		SetupOgre();
	}
	RenderCanvasSharedPtr pCanvas = pEngine.getRenderCanvas(mainCanvas);
	pCanvas->renderOneFrame();
}

void QOgreLiteWidget::resizeEvent( QResizeEvent* )
{

}

bool QOgreLiteWidget::event( QEvent * e )
{

	 return QWidget::event(e);
}

void QOgreLiteWidget::SetupOgre()
{
	NameValueMap parameters;
	parameters.set("externalWindowHandle", (size_t)(HWND)winId() );
	pEngine.createRenderCanvas(mainCanvas,&parameters);
}