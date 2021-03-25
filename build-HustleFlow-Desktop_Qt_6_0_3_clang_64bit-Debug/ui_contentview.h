/********************************************************************************
** Form generated from reading UI file 'contentview.ui'
**
** Created by: Qt User Interface Compiler version 6.0.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTENTVIEW_H
#define UI_CONTENTVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ContentView
{
public:
    QWidget *centralwidget;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuHustleFlow;

    void setupUi(QMainWindow *ContentView)
    {
        if (ContentView->objectName().isEmpty())
            ContentView->setObjectName(QString::fromUtf8("ContentView"));
        ContentView->resize(800, 600);
        centralwidget = new QWidget(ContentView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ContentView->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ContentView);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ContentView->setStatusBar(statusbar);
        menubar = new QMenuBar(ContentView);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuHustleFlow = new QMenu(menubar);
        menuHustleFlow->setObjectName(QString::fromUtf8("menuHustleFlow"));
        ContentView->setMenuBar(menubar);

        menubar->addAction(menuHustleFlow->menuAction());

        retranslateUi(ContentView);

        QMetaObject::connectSlotsByName(ContentView);
    } // setupUi

    void retranslateUi(QMainWindow *ContentView)
    {
        ContentView->setWindowTitle(QCoreApplication::translate("ContentView", "ContentView", nullptr));
        menuHustleFlow->setTitle(QCoreApplication::translate("ContentView", "HustleFlow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ContentView: public Ui_ContentView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTENTVIEW_H
