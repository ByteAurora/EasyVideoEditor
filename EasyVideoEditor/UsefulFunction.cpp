#include "UsefulFunction.h"

int UsefulFunction::getMillisecondsFromString(QString timeString) {
    int hours = timeString.mid(0, 2).toInt() * 3600000;
    int minutes = timeString.mid(3, 2).toInt() * 60000;
    int seconds = timeString.mid(6, 2).toInt() * 1000;
    int milliseconds = timeString.mid(9, 3).toInt();

    return hours + minutes + seconds + milliseconds;
}

QString UsefulFunction::getStringFromMilliseconds(int milliseconds) {
    QString strHours = QString("%1:%2:%3.%4")
        .arg(milliseconds / (3600000), 2, 10, QLatin1Char('0'))
        .arg((milliseconds % 3600000) / 60000, 2, 10, QLatin1Char('0'))
        .arg((milliseconds % 60000) / 1000, 2, 10, QLatin1Char('0'))
        .arg(milliseconds % 1000, 3, 10, QLatin1Char('0'));

    return strHours;
}

QString UsefulFunction::getDetailStringFromSeconds(int seconds) {
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int leftSeconds = seconds % 60;

    QString time("");
    if (hours > 0) time.append(QString::number(hours) + "시간 ");
    if (minutes > 0) time.append(QString::number(minutes) + "분 ");
    time.append(QString::number(leftSeconds) + "초 ");

    return time;
}

QString UsefulFunction::kor(std::string korString) {
    return QString::fromLocal8Bit(korString);
}

void UsefulFunction::showMatToLabel(QLabel* qlabel, cv::Mat* mat, cv::Size resizeData, int top, int down, int left, int right) {
    cv::cvtColor(*mat, *mat, cv::COLOR_BGR2RGB);
    cv::resize(*mat, *mat, resizeData);
    cv::copyMakeBorder(*mat, *mat, top, down, left, right, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
    qlabel->setPixmap(QPixmap::fromImage(QImage(mat->data, mat->cols, mat->rows, mat->step, QImage::Format_RGB888)));
}

void UsefulFunction::writeLog(QString filePath, QString tag, QString message) {
    QFile logFile(filePath);
    logFile.open(QFile::WriteOnly | QFile::Append | QFile::Text);
    QString logMessage;
    logMessage.append("[");
    logMessage.append(QDateTime::currentDateTime().toString());
    logMessage.append("]    [");
    logMessage.append(tag);
    logMessage.append("]: ");
    logMessage.append(message);
    logMessage.append("\n");
    QTextStream textStream(&logFile);
    textStream << logMessage;
    logFile.close();
}

QImage UsefulFunction::matToQImage(cv::Mat* mat) {
    return QImage(mat->data, mat->cols, mat->rows, mat->step, QImage::Format_RGB888);
}

cv::Mat UsefulFunction::QImageToMat(QImage* qimage) {
    return cv::Mat(qimage->height(), qimage->width(), CV_8UC3, (cv::Scalar*)qimage->scanLine(0));
}