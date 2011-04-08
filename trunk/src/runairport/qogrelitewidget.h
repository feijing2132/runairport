#ifndef QOGRELITEWIDGET_H
#define QOGRELITEWIDGET_H

#include <QWidget>
#include <RenderEngine.h>

class QOgreLiteWidget : public QWidget
{
	Q_OBJECT

public:
	QOgreLiteWidget(QWidget *parent);
	~QOgreLiteWidget();


	 bool event(QEvent *);
	 void paintEvent(QPaintEvent*);
	 void resizeEvent(QResizeEvent*);
private:
	Ogre::OgreLite::GLRenderEngine  pEngine;
	bool mbSetupOgre;
	void SetupOgre();
};

#endif // QOGRELITEWIDGET_H
