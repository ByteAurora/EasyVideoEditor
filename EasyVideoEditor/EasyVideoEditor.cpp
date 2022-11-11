#include "EasyVideoEditor.h"

EasyVideoEditor::EasyVideoEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Widgets::getInstance()->initWidgets(this);
}

EasyVideoEditor::~EasyVideoEditor()
{}
