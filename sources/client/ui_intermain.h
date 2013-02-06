/********************************************************************************
** Form generated from reading ui file 'intermain.ui'
**
** Created: Wed Jan 27 01:03:21 2010
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INTERMAIN_H
#define UI_INTERMAIN_H

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

class Ui_InterMain
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *InterMain)
    {
        if (InterMain->objectName().isEmpty())
            InterMain->setObjectName(QString::fromUtf8("InterMain"));
        InterMain->resize(600, 400);
        centralWidget = new QWidget(InterMain);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        InterMain->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(InterMain);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 25));
        InterMain->setMenuBar(menuBar);
        mainToolBar = new QToolBar(InterMain);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        InterMain->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(InterMain);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        InterMain->setStatusBar(statusBar);

        retranslateUi(InterMain);

        QMetaObject::connectSlotsByName(InterMain);
    } // setupUi

    void retranslateUi(QMainWindow *InterMain)
    {
        InterMain->setWindowTitle(QApplication::translate("InterMain", "InterMain", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(InterMain);
    } // retranslateUi

};

namespace Ui {
    class InterMain: public Ui_InterMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERMAIN_H
