#include "EasyVideoEditor.h"

EasyVideoEditor::EasyVideoEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Widgets::getInstance()->initWidgets(this);

    // Init ui.
    ui.btn_coloremphasis->setCheckable(true);
    ui.edt_coloremphasis_red->setValidator(new QIntValidator(0, 255, this));
    ui.edt_coloremphasis_green->setValidator(new QIntValidator(0, 255, this));
    ui.edt_coloremphasis_blue->setValidator(new QIntValidator(0, 255, this));

    // Init data.
    new SideMenu(ui.btn_coloremphasis, ui.w_coloremphasis);
    new SideMenu(ui.btn_changebrightness, ui.w_changebrightness);
    SideMenu::selectSideMenu(ui.btn_coloremphasis);

    // Init signal, slot.
    connect(ui.btn_coloremphasis, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_changebrightness, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.sd_coloremphasis_red, SIGNAL(valueChanged(int)), this, SLOT(setLineEditBySlider(int)));
    connect(ui.sd_coloremphasis_green, SIGNAL(valueChanged(int)), this, SLOT(setLineEditBySlider(int)));
    connect(ui.sd_coloremphasis_blue, SIGNAL(valueChanged(int)), this, SLOT(setLineEditBySlider(int)));;
    connect(ui.edt_coloremphasis_red, SIGNAL(textChanged(QString)), this, SLOT(setSliderByLineEdit(QString)));;
    connect(ui.edt_coloremphasis_green, SIGNAL(textChanged(QString)), this, SLOT(setSliderByLineEdit(QString)));
    connect(ui.edt_coloremphasis_blue, SIGNAL(textChanged(QString)), this, SLOT(setSliderByLineEdit(QString)));
}

EasyVideoEditor::~EasyVideoEditor()
{}

void EasyVideoEditor::sideMenuClicked() {
    SideMenu::selectSideMenu((QPushButton*)sender());
}

void EasyVideoEditor::setLineEditBySlider(int value) {
    QObject* senderObject = sender();
    if (senderObject == ui.sd_coloremphasis_red) ui.edt_coloremphasis_red->setText(QString::number(value));
    else if (senderObject == ui.sd_coloremphasis_green) ui.edt_coloremphasis_green->setText(QString::number(value));
    else if (senderObject == ui.sd_coloremphasis_blue) ui.edt_coloremphasis_blue->setText(QString::number(value));

}

void EasyVideoEditor::setSliderByLineEdit(QString value) {
    QObject* senderObject = sender();
    if (senderObject == ui.edt_coloremphasis_red) ui.sd_coloremphasis_red->setValue(value.toInt());
    else if (senderObject == ui.edt_coloremphasis_green) ui.sd_coloremphasis_green->setValue(value.toInt());
    else if (senderObject == ui.edt_coloremphasis_blue) ui.sd_coloremphasis_blue->setValue(value.toInt());
}