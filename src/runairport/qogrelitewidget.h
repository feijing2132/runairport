#ifndef QOGRELITEWIDGET_H
#define QOGRELITEWIDGET_H

#include <QGLWidget>
#include "../ogrelite/ogreliteptr.h"



//class QOgreLiteWidgetPrivate;
class QOgreLiteWidget : public QGLWidget
{
	Q_OBJECT
	//Q_DECLARE_PRIVATE(QOgreLiteWidget)
public:
	QOgreLiteWidget(QWidget *parent);
	~QOgreLiteWidget();

	void timerEvent(QTimerEvent* evt);		
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();
private:	
	Ogre::OgreLite::inst_ptr<Ogre::OgreLite::IRenderEngine> mpEngine;
};


#endif // QOGRELITEWIDGET_H
