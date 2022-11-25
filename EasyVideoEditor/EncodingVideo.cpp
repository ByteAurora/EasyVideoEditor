#include "EncodingVideo.h"

EncodingVideo::EncodingVideo(QObject* parent, QString encodingType, QString saveFilePath) : QThread(parent) {
    this->encodingType = encodingType;
    this->saveFilePath = saveFilePath;
    this->saveFileName = saveFilePath;
}

void EncodingVideo::setData(QString encodingType, QString saveFilePath) {
    this->encodingType = encodingType;
    this->saveFilePath = saveFilePath;
    this->saveFileName = saveFilePath;
}

void EncodingVideo::run() {
    QWidget* encodingPage = Widgets::getInstance()->contentArea->findChild<QWidget*>("w_encodingpage");
    QLabel* encodingFileName = encodingPage->findChild<QLabel*>("lbl_encoding_filename");
    QLabel* encodingLeftTime = encodingPage->findChild<QLabel*>("lbl_encoding_lefttime");
    QMenuBar* mbEveMenu = Widgets::getInstance()->menuBar;

    // Init UI.
    encodingPage->setVisible(true);
    encodingFileName->setText(saveFileName);
    emit updateProgress(0);
    encodingLeftTime->setText("남은 시간 계산 중...");
    mbEveMenu->setEnabled(false);

    int fourcc;

    if (encodingType == "avi") {
        fourcc = cv::VideoWriter::fourcc('D', 'I', 'V', 'X');
    }
    else if (encodingType == "mp4") {
        fourcc = cv::VideoWriter::fourcc('M', 'P', '4', 'V');
    }
    else if (encodingType == "wmv") {
        fourcc = cv::VideoWriter::fourcc('M', 'P', '4', '3');
    }
    else if (encodingType == "mov") {
        fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    }

    cv::TickMeter tickMeter;
    cv::VideoWriter outputVideo(saveFilePath.toStdString(), fourcc, EveProject::getInstance()->getBaseFps(), cv::Size(EasyVideoEditor::outputVideoWidth, EasyVideoEditor::outputVideoHeight));
    std::vector<Frame*>* saveFrameList = EveProject::getInstance()->getFrameList();
    cv::Mat frame;
    int totalFrameCount = saveFrameList->size();
    int progressIncreaseCount = totalFrameCount / 100;
    if (progressIncreaseCount == 0) progressIncreaseCount = 1;
    bool processFramePerSecondSet = false;
    int processFramePerSecond = 0;

    int beforeSourceId = -1;
    int beforeSourceFrameIndex = -1;
    Frame* currentFrame;

    tickMeter.reset();
    tickMeter.start();
    for (int loop = 0; loop < totalFrameCount; loop++) {
        currentFrame = saveFrameList->at(loop)->getCommandAppliedFrameData(beforeSourceId, beforeSourceFrameIndex, &frame, true);
        beforeSourceId = currentFrame->getSourceId();
        beforeSourceFrameIndex = currentFrame->getSourceFrameIndex();
        
        if (frame.cols != EasyVideoEditor::outputVideoWidth || frame.rows != EasyVideoEditor::outputVideoHeight) {
            cv::resize(frame, frame, cv::Size(EasyVideoEditor::outputVideoWidth, EasyVideoEditor::outputVideoHeight));
        }

        outputVideo << frame;
        if (loop % progressIncreaseCount == 0) {
            emit updateProgress(loop / progressIncreaseCount);
        }

        tickMeter.stop();
        if (tickMeter.getTimeSec() > 1) {
            tickMeter.reset();
            if (processFramePerSecondSet) {
                encodingLeftTime->setText("남은 시간: " + UsefulFunction::getDetailStringFromSeconds((totalFrameCount - loop) / processFramePerSecond));
            } else {
                processFramePerSecondSet = true;
                processFramePerSecond = loop;
            }
        }
        tickMeter.start();
    }
    tickMeter.stop();

    mbEveMenu->setEnabled(true);
    encodingPage->setVisible(false);
}

