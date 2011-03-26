#include "stdafx.h"
#include "runairport.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	runairport w;
	w.show();
	return a.exec();
}
