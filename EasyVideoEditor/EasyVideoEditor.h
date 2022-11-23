#pragma once

#include <QtWidgets/QMainWindow>
#include <QRegularExpression>
#include <QValidator>
#include <QFileDialog>
#include <QMessageBox>
#include <QMutex>
#include <QEvent>
#include <QKeyEvent>
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

    // Editor mode.
    static Mode mode;

    // Size data used to show in qlabel.
    static cv::Size resizeData;
    static int top;
    static int down;
    static int left;
    static int right;
private:
    Ui::EasyVideoEditorClass ui;

    // Window showed state.
    bool workAfterMainWindowShowedCalled = false;

    // A Frame object to show real-time editing effects.
    Frame editingFrame;
private:
    // A function called after a window displayed.
    void workAfterMainWindowShowed();
    void updateSampleFrame();

    // Clear project data and ui elements.
    void clear();

    // Load new video project.
    void newProject();

    bool event(QEvent* e);
    void keyPressEvent(QKeyEvent* e);
private slots:
    // Menu slots.
    void newProjectMenuClicked();
    void encodingToMp4MenuClicked();
    void encodingToAviMenuClicked();
    void encodingToWmvMenuClicked();
    void encodingToMovMenuClicked();
    void exitMenuClicked();

    // Grouped slots.
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
