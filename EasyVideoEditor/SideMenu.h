#pragma once

#include <QPushButton>
#include <QWidget>
#include <iostream>
#include <vector>

class SideMenu
{
private:
    static std::vector<SideMenu*> sideMenuList;
    QPushButton* sideMenuButton;
    QWidget* sideMenuPage;
public:
    SideMenu();
    SideMenu(QPushButton* sideMenuButton, QWidget* sideMenuPage);
    ~SideMenu();

    static void selectSideMenu(QPushButton* sideMenuButton);
    void select(bool selectState);
public:
    void setSideMenuButton(QPushButton* sideMenuButton);
    QPushButton* getSideMenuButton();
    void setSideMenuPage(QWidget* sideMenuPage);
    QWidget* getSideMenuPage();
};

