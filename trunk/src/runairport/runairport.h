#ifndef RUNAIRPORT_H
#define RUNAIRPORT_H

#include <QtGui/QMainWindow>
#include "ui_runairport.h"

class runairport : public QMainWindow
{
	Q_OBJECT

public:
	runairport(QWidget *parent = 0, Qt::WFlags flags = 0);
	~runairport();

private:
	Ui::runairportClass ui;
};

#endif // RUNAIRPORT_H
