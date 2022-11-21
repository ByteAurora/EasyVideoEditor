#pragma once

#include <QWidget>
#include <QString>
#include <QLabel>
#include <opencv2/opencv.hpp>

class UsefulFunction
{
public:
    static int getMillisecondsFromString(QString timeString);
    static QString getStringFromMilliseconds(int milliseconds);
    static QString kor(std::string korString);
    static void showMatToLabel(QLabel* qlabel, cv::Mat* mat, cv::Size resizeData, int top, int down, int left, int right);
};

