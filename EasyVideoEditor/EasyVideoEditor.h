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
public:
    static QString kor(std::string korString);
private:
    Ui::EasyVideoEditorClass ui;
    bool workAfterMainWindowShowedCalled = false;
private:
    void workAfterMainWindowShowed();
    bool event(QEvent* event);
private slots:
    void setLineEditBySlider(int value);
    void setSliderByLineEdit(QString value);
    void sideMenuClicked();
};
