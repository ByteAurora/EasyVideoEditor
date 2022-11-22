#pragma once

#include <QtWidgets/QMainWindow>
#include <QRegularExpression>
#include <QValidator>
#include <QFileDialog>
#include <QMessageBox>
#include <QMutex>
#include "SideMenu.h"
#include "ui_EasyVideoEditor.h"
#include "Widgets.h"
#include "EveProject.h"
#include "UsefulFunction.h"
#include "PlayVideo.h"

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

class PlayVideo;

class EasyVideoEditor : public QMainWindow
{
    Q_OBJECT

public:
    enum Mode{ MODE_EDIT, MODE_WATCH_PLAY, MODE_WATCH_PAUSE };
    EasyVideoEditor(QWidget* parent = nullptr);
    ~EasyVideoEditor();
public:
    static QMutex mutex;
    static Mode mode;
    static cv::Size resizeData;
    static int top;
    static int down;
    static int left;
    static int right;
private:
    Ui::EasyVideoEditorClass ui;
    bool workAfterMainWindowShowedCalled = false;
    Frame editingFrame;
private:
    void workAfterMainWindowShowed();
    bool event(QEvent* event);
private slots:
    void setLineEditBySlider(int value);
    void setSliderByLineEdit(QString value);
    void sideMenuClicked();

    // Video control slots.
    void playButtonClicked();
    void pauseButtonClicked();
    void resetButtonClicked();
    void forward5SecondsButtonclicked();
    void backward5SecondsButtonClicked();

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

    // test
    void addImageSelectButtonClicked();
    void addVideoSelectButtonClicked();
};
