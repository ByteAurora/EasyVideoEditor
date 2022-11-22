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
    cv::Mat showFrame; // 여기다가 실제 파일을 불러와서
    int frameIndex = startIndex;
    int beforeFrameIndex = frameIndex - 1;
    Frame* currentFrame = EveProject::getInstance()->getCurrentFrame();
    Frame* beforeFrame = currentFrame;

    while (frameIndex <= endIndex) {
        tickMeter.reset();
        EasyVideoEditor::mutex.lock();
        tickMeter.start();

        frameIndex = EveProject::getInstance()->getCurrentFrameNumber();
        if (EasyVideoEditor::mode != EasyVideoEditor::Mode::MODE_WATCH_PLAY || frameIndex > endIndex) {
            EasyVideoEditor::mutex.unlock();
            break;
        }

        currentFrame = EveProject::getInstance()->getCurrentFrame();
        lblCurrentPlayTime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(frameIndex)));
        sdVideoProgress->setValue(frameIndex);

        if(frameIndex != startIndex)
            // 현재 보고 있는 프레임을 반환해주고 를 1증가
            EveProject::getInstance()->getCurrentFrameAndUpdate()->getCommandAppliedFrameData(&showFrame, 
                (frameIndex > beforeFrameIndex + 1) 
                || (frameIndex < beforeFrameIndex) 
                || (currentFrame->getSourceId() != beforeFrame->getSourceId()) 
                || (currentFrame->getSourceId() == beforeFrame->getSourceId() && currentFrame->getSourceFrameIndex() < beforeFrame->getSourceFrameIndex()
                || currentFrame->getSourceFrameIndex() > beforeFrame->getSourceFrameIndex() + 1));
        else
            EveProject::getInstance()->getCurrentFrameAndUpdate()->getCommandAppliedFrameData(&showFrame, true);
        
        UsefulFunction::showMatToLabel(lblVideoFrame, &showFrame, EasyVideoEditor::resizeData, EasyVideoEditor::top, EasyVideoEditor::down, EasyVideoEditor::left, EasyVideoEditor::right);
        
        tickMeter.stop();
        EasyVideoEditor::mutex.unlock();

        int processingTime = tickMeter.getTimeMilli();
        if (processingTime < delay) {
            msleep(delay - processingTime);
        }

        beforeFrame = currentFrame;
        beforeFrameIndex = frameIndex;
    }

    if (frameIndex > endIndex) {
        EasyVideoEditor::mutex.lock();
        btnPlay->setVisible(true);
        btnPause->setVisible(false);
        EveProject::getInstance()->setCurrentFrameNumber(endIndex);
        EasyVideoEditor::mode = EasyVideoEditor::Mode::MODE_WATCH_PAUSE;
        EasyVideoEditor::mutex.unlock();
    }
}
