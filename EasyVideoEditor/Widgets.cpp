#include "Widgets.h"

Widgets* Widgets::instance = NULL;

Widgets::Widgets() {
    window = NULL;
    contentArea = NULL;
    menuBar = NULL;
}

Widgets::~Widgets() {

}

Widgets* Widgets::getInstance() {
    if (instance == NULL) {
        instance = new Widgets();
    }

    return instance;
}

void Widgets::initWidgets(QMainWindow *mainWindow) {
    window = mainWindow;
    contentArea = window->findChild<QWidget*>("w_contentarea");
    menuBar = window->findChild<QObject*>("mb_evemenu");
}