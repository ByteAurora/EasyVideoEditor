#include "EncodingVideo.h"

EncodingVideo::EncodingVideo(QObject* parent, QString encodingType, QString saveFilePath) : QThread(parent) {
    this->encodingType = encodingType;
    this->saveFilePath = saveFilePath;
    QFile saveFile(saveFilePath);
    this->saveFileName = saveFile.fileName();
}

void EncodingVideo::run() {
    QWidget* encodingPage = Widgets::getInstance()->contentArea->findChild<QWidget*>("w_encodingpage");
    QLabel* encodingFileName = encodingPage->findChild<QLabel*>("lbl_encoding_filename");
    QProgressBar* encodingProgress = encodingPage->findChild<QProgressBar*>("pb_encoding_progress");
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
    bool processFramePerSecondSet = false;
    int processFramePerSecond = 0;

    tickMeter.reset();
    tickMeter.start();
    for (int loop = 0; loop < totalFrameCount; loop++) {
        saveFrameList->at(loop)->getCommandAppliedFrameData(&frame, false);
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

