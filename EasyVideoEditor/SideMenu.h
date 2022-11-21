#pragma once

#include <QPushButton>
#include <QWidget>
#include <iostream>
#include <vector>

/*
* @version  v1.0.0
* @author   Sohn Young Jin
* @since    v1.0.0
*
* The SideMenu class is a class connected to SideMenu-related widgets in EveProject.
*/
class SideMenu
{
private:
    // A list containing all SideMenu created.
    static std::vector<SideMenu*> sideMenuList;

    // Button on side menu.
    QPushButton* sideMenuButton;

    // Page on side menu.
    QWidget* sideMenuPage;
public:
    // Default constructor.
    SideMenu();

    // Custom constructor.
    SideMenu(QPushButton* sideMenuButton, QWidget* sideMenuPage);

    // Default destructor.
    ~SideMenu();

    // Select side menu and change all side menus widgets state.
    static void selectSideMenu(QPushButton* sideMenuButton);

    // Change side menu widgets state.
    void select(bool selectState);
public:
    // Side menu button setter.
    void setSideMenuButton(QPushButton* sideMenuButton);
    // Side menu button getter.
    QPushButton* getSideMenuButton();

    // Side menu page setter.
    void setSideMenuPage(QWidget* sideMenuPage);
    // Side menu page getter.
    QWidget* getSideMenuPage();
};

