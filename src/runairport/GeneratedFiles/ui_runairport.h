/********************************************************************************
** Form generated from reading UI file 'runairport.ui'
**
** Created: Wed Mar 23 10:52:48 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUNAIRPORT_H
#define UI_RUNAIRPORT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_runairportClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *runairportClass)
    {
        if (runairportClass->objectName().isEmpty())
            runairportClass->setObjectName(QString::fromUtf8("runairportClass"));
        runairportClass->resize(600, 400);
        menuBar = new QMenuBar(runairportClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        runairportClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(runairportClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        runairportClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(runairportClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        runairportClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(runairportClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        runairportClass->setStatusBar(statusBar);

        retranslateUi(runairportClass);

        QMetaObject::connectSlotsByName(runairportClass);
    } // setupUi

    void retranslateUi(QMainWindow *runairportClass)
    {
        runairportClass->setWindowTitle(QApplication::translate("runairportClass", "runairport", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class runairportClass: public Ui_runairportClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUNAIRPORT_H
