#include "SideMenu.h"

std::vector<SideMenu*> SideMenu::sideMenuList;

SideMenu::SideMenu() {
    sideMenuButton = NULL;
    sideMenuPage = NULL;
    sideMenuList.push_back(this);
}

SideMenu::SideMenu(QPushButton* sideMenuButton, QWidget* sideMenuPage) {
    this->sideMenuButton = sideMenuButton;
    this->sideMenuPage = sideMenuPage;
    sideMenuList.push_back(this);
}

SideMenu::~SideMenu() {

}

void SideMenu::selectSideMenu(QPushButton* sideMenuButton) {
    for (int loop = 0; loop < sideMenuList.size(); loop++)
        sideMenuList[loop]->select(sideMenuList[loop]->sideMenuButton == sideMenuButton);
}

void SideMenu::select(bool selectState) {
    sideMenuButton->setChecked(selectState);
    sideMenuPage->setVisible(selectState);
}

void SideMenu::setSideMenuButton(QPushButton* sideMenuButton) {
    this->sideMenuButton = sideMenuButton;
}

QPushButton* SideMenu::getSideMenuButton() {
    return sideMenuButton;
}

void SideMenu::setSideMenuPage(QWidget* sideMenuPage) {
    this->sideMenuPage = sideMenuPage;
}

QWidget* SideMenu::getSideMenuPage() {
    return sideMenuPage;
}