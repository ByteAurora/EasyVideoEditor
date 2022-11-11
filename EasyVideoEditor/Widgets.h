#pragma once

#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qmainwindow.h>

/*
2022-11-11. Created by Sohn Young Jin
Widgets class control all included widgets in QMainWindow. It is implemented as a singleton pattern, so it can be accessed from anywhere in your code.
*/
class Widgets
{
private:
    Widgets();
    ~Widgets();
private:
    static Widgets* instance;
    QMainWindow* window;
    QWidget* contentArea;
    QObject* menuBar;
public:
    // Get instance of Widgets class.
    static Widgets* getInstance();

    // Initialize ui widgets from QMainWindow.
    void initWidgets(QMainWindow* mainWindow);
};