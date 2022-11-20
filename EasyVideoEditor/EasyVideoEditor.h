#pragma once

#include <QtWidgets/QMainWindow>
#include <QRegularExpression>
#include <QValidator>
#include "SideMenu.h"
#include "ui_EasyVideoEditor.h"
#include "Widgets.h"

class EasyVideoEditor : public QMainWindow
{
    Q_OBJECT

public:
    EasyVideoEditor(QWidget *parent = nullptr);
    ~EasyVideoEditor();

private:
    Ui::EasyVideoEditorClass ui;

private slots:
    void setLineEditBySlider(int value);
    void setSliderByLineEdit(QString value);
    void sideMenuClicked();
};
