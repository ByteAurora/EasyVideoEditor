#pragma once

#include <QtWidgets/QMainWindow>
#include <QRegularExpression>
#include <QValidator>
#include <QFileDialog>
#include <QMessageBox>
#include <QMutex>
#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsEffect>
#include "SideMenu.h"
#include "ui_EasyVideoEditor.h"
#include "Widgets.h"
#include "EveProject.h"
#include "UsefulFunction.h"
#include "PlayVideo.h"
#include "EncodingVideo.h"

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
#include "ChangePlaySpeed.h"
#include "AddSubtitle.h"

class EncodingVideo;
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
    static QMetaObject::Connection encodingVideoThreadConnection;
private:
    Ui::EasyVideoEditorClass ui;

    // Window showed state.
    bool workAfterMainWindowShowedCalled = false;

    // A Frame object to show real-time editing effects.
    Frame editingFrame;

    EncodingVideo* encodingVideoThread = NULL;
    PlayVideo* playVideoThread = NULL;
private:
    // A function called after a window displayed.
    void workAfterMainWindowShowed();

    // Clear project data and ui elements.
    void clear();

    // Load new video project.
    void newProject();

    // Save edited video.
    void encodingVideo(QString encodingType);

    // Update information area.
    void updateInformationArea();

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
    void videoProgressSliderMoved(int value);
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
    void changePlaySpeedButtonClicked();
    void addSubtitleButtonClicked();
    void addSubtitleCurrentFrameButtonClicked();
    void addSubtitleAllFrameButtonClicked();
    void addSubtitleRangeFrameButtonClicked();
    void addImageSelectButtonClicked();
    void addImageCurrentFrameButtonClicked();
    void addImageAllFrameButtonClicked();
    void addImageRangeFrameButtonClicked();
    void addVideoSelectButtonClicked();
    void chromakeyFilePickerButtonClicked();

    void updateEncodingProgressBar(int value);
    void updateSampleFrame();
};
