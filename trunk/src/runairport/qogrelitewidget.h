#ifndef QOGRELITEWIDGET_H
#define QOGRELITEWIDGET_H

#include <QGLWidget>


class QOgreLiteWidget : public QGLWidget
{
	Q_OBJECT
	
public:
	QOgreLiteWidget(QWidget *parent);
	~QOgreLiteWidget();


	void timerEvent(QTimerEvent* evt);	

	
	 void paintEvent(QPaintEvent*);
	 void resizeEvent(QResizeEvent*);
private:
	
	bool mbSetupOgre;
	void SetupOgre();
};


#endif // QOGRELITEWIDGET_H
