#include "PlayVideo.h"

PlayVideo::PlayVideo(QObject* parent) : QThread(parent) {

}

void PlayVideo::run() {
    EasyVideoEditor::mutex.lock();
    int startIndex = EveProject::getInstance()->getCurrentFrameNumber();
    int endIndex = EveProject::getInstance()->getFrameList()->size() - 1;
    int delay = EveProject::getInstance()->getBaseDelay();
    QLabel* lblVideoFrame = Widgets::getInstance()->contentArea->findChild<QWidget*>("w_videoarea")->findChild<QLabel*>("lbl_videoframe");
    QLabel* lblCurrentPlayTime = Widgets::getInstance()->contentArea->findChild<QWidget*>("w_videoarea")->findChild<QWidget*>("w_videocontrolarea")->findChild<QLabel*>("lbl_currentplaytime");
    QLabel* lblMaxPlayTime = Widgets::getInstance()->contentArea->findChild<QWidget*>("w_videoarea")->findChild<QWidget*>("w_videocontrolarea")->findChild<QLabel*>("lbl_maxplaytime");
    QSlider* sdVideoProgress = Widgets::getInstance()->contentArea->findChild<QWidget*>("w_videoarea")->findChild<QWidget*>("w_videocontrolarea")->findChild<QSlider*>("sd_videoprogress");
    QPushButton* btnPlay = Widgets::getInstance()->contentArea->findChild<QWidget*>("w_videoarea")->findChild<QWidget*>("w_videocontrolarea")->findChild<QPushButton*>("btn_play");;
    QPushButton* btnPause = Widgets::getInstance()->contentArea->findChild<QWidget*>("w_videoarea")->findChild<QWidget*>("w_videocontrolarea")->findChild<QPushButton*>("btn_pause");;
    
    lblMaxPlayTime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(endIndex)));
    sdVideoProgress->setMinimum(0);
    sdVideoProgress->setMaximum(endIndex);
    EasyVideoEditor::mutex.unlock();

    cv::TickMeter tickMeter;
    cv::Mat showFrame;
    int frameIndex = startIndex;
    Frame* currentFrame = EveProject::getInstance()->getCurrentFrame();
    Frame* beforeFrame;
    int beforeSourceId = -1;
    int beforeSourceFrameIndex = -1;

    while (frameIndex <= endIndex) {
        tickMeter.reset();
        EasyVideoEditor::mutex.lock();
        tickMeter.start();

        frameIndex = EveProject::getInstance()->getCurrentFrameNumber();
        if (EasyVideoEditor::mode != EasyVideoEditor::Mode::MODE_WATCH_PLAY || frameIndex > endIndex) {
            btnPlay->setVisible(true);
            btnPause->setVisible(false);
            EasyVideoEditor::mutex.unlock();
            break;
        }

        currentFrame = EveProject::getInstance()->getCurrentFrame();
        lblCurrentPlayTime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(frameIndex)));
        sdVideoProgress->setValue(frameIndex);

        beforeFrame = EveProject::getInstance()->getCurrentFrameAndUpdate()->getCommandAppliedFrameData(beforeSourceId, beforeSourceFrameIndex, &showFrame, true);
        beforeSourceId = beforeFrame->getSourceId();
        beforeSourceFrameIndex = beforeFrame->getSourceFrameIndex();

        UsefulFunction::showMatToLabel(lblVideoFrame, &showFrame, EasyVideoEditor::resizeData, EasyVideoEditor::top, EasyVideoEditor::down, EasyVideoEditor::left, EasyVideoEditor::right);
        
        tickMeter.stop();
        EasyVideoEditor::mutex.unlock();

        int processingTime = tickMeter.getTimeMilli();
        if (processingTime < delay) {
            msleep(delay - processingTime);
        }
    }

    if (frameIndex > endIndex) {
        EasyVideoEditor::mutex.lock();
        EveProject::getInstance()->setCurrentFrameNumber(endIndex);
        EasyVideoEditor::mode = EasyVideoEditor::Mode::MODE_WATCH_PAUSE;
        EasyVideoEditor::mutex.unlock();
    }
}
