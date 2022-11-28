#include "VideoProgressEventFilter.h"

VideoProgressEventFilter::VideoProgressEventFilter(QLabel* videoFrame, QSlider* videoProgress, QLabel* currentPlayTime, QObject* parent) : QObject(parent)
{
    this->videoFrame = videoFrame;
    this->videoProgress = videoProgress;
    this->currentPlayTime = currentPlayTime;
}

bool VideoProgressEventFilter::eventFilter(QObject* obj, QEvent* e)
{
    if (e->type() == QEvent::KeyPress && EasyVideoEditor::mode != EasyVideoEditor::Mode::MODE_EDIT) {
        if (((QKeyEvent*)e)->key() == Qt::Key_Left) {
            EasyVideoEditor::mutex.lock();
            EveProject::getInstance()->forward1Frame();
            videoProgress->setValue(EveProject::getInstance()->getCurrentFrameNumber());
            currentPlayTime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(EveProject::getInstance()->getCurrentFrameNumber())));
            cv::Mat showFrame;
            EveProject::getInstance()->getCurrentFrame()->getCommandAppliedFrameData(-1, -1, &showFrame, true);
            UsefulFunction::showMatToLabel(videoFrame, &showFrame, EasyVideoEditor::resizeData, EasyVideoEditor::top, EasyVideoEditor::down, EasyVideoEditor::left, EasyVideoEditor::right);
            EasyVideoEditor::mutex.unlock();
            return true;
        }
        else if (((QKeyEvent*)e)->key() == Qt::Key_Right) {
            EasyVideoEditor::mutex.lock();
            EveProject::getInstance()->backward1Frame();
            videoProgress->setValue(EveProject::getInstance()->getCurrentFrameNumber());
            currentPlayTime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(EveProject::getInstance()->getCurrentFrameNumber())));
            cv::Mat showFrame;
            EveProject::getInstance()->getCurrentFrame()->getCommandAppliedFrameData(-1, -1, &showFrame, true);
            UsefulFunction::showMatToLabel(videoFrame, &showFrame, EasyVideoEditor::resizeData, EasyVideoEditor::top, EasyVideoEditor::down, EasyVideoEditor::left, EasyVideoEditor::right);
            EasyVideoEditor::mutex.unlock();
            return true;
        }
    }

    return QObject::eventFilter(obj, e);
}