/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_Scene;
    QAction *actionSave_Image;
    QAction *actionEquilateral_Triangle;
    QAction *actionQuit_Esc;
    QWidget *centralWidget;
    QGraphicsView *scene_display;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuScenes;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(612, 612);
        actionLoad_Scene = new QAction(MainWindow);
        actionLoad_Scene->setObjectName("actionLoad_Scene");
        actionSave_Image = new QAction(MainWindow);
        actionSave_Image->setObjectName("actionSave_Image");
        actionEquilateral_Triangle = new QAction(MainWindow);
        actionEquilateral_Triangle->setObjectName("actionEquilateral_Triangle");
        actionQuit_Esc = new QAction(MainWindow);
        actionQuit_Esc->setObjectName("actionQuit_Esc");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        scene_display = new QGraphicsView(centralWidget);
        scene_display->setObjectName("scene_display");
        scene_display->setEnabled(false);
        scene_display->setGeometry(QRect(50, 25, 512, 512));
        scene_display->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scene_display->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scene_display->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scene_display->setInteractive(false);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 612, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuScenes = new QMenu(menuBar);
        menuScenes->setObjectName("menuScenes");
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuScenes->menuAction());
        menuFile->addAction(actionLoad_Scene);
        menuFile->addAction(actionSave_Image);
        menuFile->addAction(actionQuit_Esc);
        menuScenes->addAction(actionEquilateral_Triangle);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLoad_Scene->setText(QCoreApplication::translate("MainWindow", "Load Scene (Ctrl+O)", nullptr));
#if QT_CONFIG(shortcut)
        actionLoad_Scene->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_Image->setText(QCoreApplication::translate("MainWindow", "Save Image (Ctrl+S)", nullptr));
#if QT_CONFIG(shortcut)
        actionSave_Image->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionEquilateral_Triangle->setText(QCoreApplication::translate("MainWindow", "Equilateral Triangle", nullptr));
        actionQuit_Esc->setText(QCoreApplication::translate("MainWindow", "Quit (Esc)", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuScenes->setTitle(QCoreApplication::translate("MainWindow", "Scenes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
