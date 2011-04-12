#ifndef QOGRELITEWIDGET_H
#define QOGRELITEWIDGET_H

#include <QWidget>
#include <RenderEngine.h>
#include <private/qwidget_p.h>

class QOgreLiteWidgetPrivate : public QWidgetPrivate
{

};

class QOgreLiteWidget : public QWidget
{
	Q_OBJECT

	Q_DECLARE_PRIVATE(QOgreLiteWidget)
public:
	QOgreLiteWidget(QWidget *parent);
	~QOgreLiteWidget();


	void timerEvent(QTimerEvent* evt);

	 bool event(QEvent *);
	 void paintEvent(QPaintEvent*);
	 void resizeEvent(QResizeEvent*);
private:
	Ogre::OgreLite::GLRenderEngine  pEngine;
	bool mbSetupOgre;
	void SetupOgre();
};


#endif // QOGRELITEWIDGET_H
