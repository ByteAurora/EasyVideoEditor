#pragma once

#include <QtWidgets/QMainWindow>
#include <QRegularExpression>
#include <QValidator>
#include <QFileDialog>
#include <QMessageBox>
#include "SideMenu.h"
#include "ui_EasyVideoEditor.h"
#include "Widgets.h"
#include "EveProject.h"

class EasyVideoEditor : public QMainWindow
{
    Q_OBJECT

public:
    EasyVideoEditor(QWidget* parent = nullptr);
    ~EasyVideoEditor();
private:
    Ui::EasyVideoEditorClass ui;
    bool workAfterMainWindowShowedCalled = false;
private slots:
    void setLineEditBySlider(int value);
    void setSliderByLineEdit(QString value);
    void sideMenuClicked();
    void workAfterMainWindowShowed();
    bool event(QEvent* event);
};
