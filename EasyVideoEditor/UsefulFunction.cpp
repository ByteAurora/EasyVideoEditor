#include "UsefulFunction.h"

int UsefulFunction::getMillisecondsFromString(QString timeString) {
    int hours = timeString.mid(0, 2).toInt();
    int minutes = timeString.mid(3, 2).toInt();
    int seconds = timeString.mid(6, 2).toInt();
    int milliseconds = timeString.mid(9, 3).toInt();

    return hours * minutes * seconds * 1000 + milliseconds;
}

QString UsefulFunction::getStringFromMilliseconds(int milliseconds) {
    QString strHours = QString("%1:%2:%3.%4")
        .arg(milliseconds / (3600000), 2, 10, QLatin1Char('0'))
        .arg((milliseconds % 3600000) / 60000, 2, 10, QLatin1Char('0'))
        .arg((milliseconds % 60000) / 1000, 2, 10, QLatin1Char('0'))
        .arg(milliseconds % 1000, 2, 10, QLatin1Char('0'));

    return strHours;
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
