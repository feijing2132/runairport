#include "StdAfx.h"
#include "qogrelitewidget.h"
#include <QPixmap>
using namespace Ogre;
using namespace OgreLite;

static String mainCanvas = ("MainCanvas"); 

QOgreLiteWidget::QOgreLiteWidget(QWidget *parent)
	: QWidget(parent,Qt::WFlags(Qt::MSWindowsOwnDC))
{
	mbSetupOgre = false; 
	//setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);
	setAutoFillBackground(true); // for compatibility
	startTimer(1);
}

QOgreLiteWidget::~QOgreLiteWidget()
{

}

void QOgreLiteWidget::paintEvent( QPaintEvent*evt )
{
	Q_UNUSED(evt);

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
	update();
}

bool QOgreLiteWidget::event( QEvent * e )
{
	/*Q_D(QWidget);*/
	if (e->type() == QEvent::Paint) {
	/*	QPoint offset;
		QPaintDevice *redirectedDevice = d->redirected(&offset);
		if (redirectedDevice && redirectedDevice->devType() == QInternal::Pixmap) {
			d->restoreRedirected();
			QPixmap pixmap = renderPixmap();
			d->setRedirected(redirectedDevice, offset);
			QPainter p(redirectedDevice);
			p.drawPixmap(-offset, pixmap);
			return true;
		}*/
	}
	 return QWidget::event(e);
}

void QOgreLiteWidget::SetupOgre()
{
	NameValueMap parameters;
	parameters.set("externalWindowHandle", (size_t)(HWND)winId() );
	pEngine.createRenderCanvas(mainCanvas,&parameters);
}

void QOgreLiteWidget::timerEvent( QTimerEvent* evt )
{
	Q_UNUSED(evt);
	update();
}
