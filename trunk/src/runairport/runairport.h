#ifndef RUNAIRPORT_H
#define RUNAIRPORT_H

#include <QtGui/QMainWindow>
#include "ui_runairport.h"
#include "glview.h"
#include "qogrelitewidget.h"

QT_BEGIN_NAMESPACE

class dUi_runairportClass : public Ui_runairportClass
{
public:
	QVBoxLayout *ogreLayout;	
	//QWidget ogreWidget;
public:
	void setupOgreWidget()
	{
		ogreLayout =new QVBoxLayout;
		/*ogreWidget.setGeometry (100,100,640,480) ;
		ogreWidget.setLayout(ogreLayout);*/
		centralWidget->setLayout(ogreLayout);
		ogreLayout->addWidget(new glView(centralWidget));
		ogreLayout->addWidget(new QOgreLiteWidget(centralWidget));
		//ogreWidget.show();
	}
};

QT_END_NAMESPACE

class runairport : public QMainWindow
{
	Q_OBJECT

public:
	runairport(QWidget *parent = 0, Qt::WFlags flags = 0);
	~runairport();

private:
	dUi_runairportClass ui;
};

#endif // RUNAIRPORT_H
