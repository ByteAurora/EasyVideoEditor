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
#include "UsefulFunction.h"

// Command class.
#include "ColorEmphasis.h"
#include "ChangeBrightness.h"
#include "ChangeContrast.h"
#include "Filter.h"
#include "Chromakey.h"
#include "Transition.h"
#include "AddImage.h"
#include "AddVideo.h"
#include "CutVideo.h"
#include "Resize.h"
#include "ChangePlaySpeed.h"
#include "AddSubtitle.h"

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

    // Apply button slots.
    void colorEmphasisApplyButtonClicked();
    void changeBrightnessApplyButtonClicked();
    void changeContrastApplyButtonClicked();
    void filterApplyButtonClicked();
    void chromakeyApplyButtonClicked();
    void transitionApplyButtonClicked();
    void addImageApplyButtonClicked();
    void addVideoApplyButtonClicked();
    void cutVideoApplyButtonClicked();
    void resizeApplyButtonClicked();
    void changePlaySpeedButtonClicked();
    void addSubtitleButtonClicked();
};
