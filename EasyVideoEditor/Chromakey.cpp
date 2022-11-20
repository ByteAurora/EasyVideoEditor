#include "Chromakey.h"

Chromakey::Chromakey() {
    hueMin = 0;
    hueMax = 180;
    saturationMin = 0;
    saturationMax = 255;
    valueMin = 0;
    valueMax = 255;
    reverse = false;
    backgroundImageResourceId = 0;
}

Chromakey::Chromakey(int hueMin, int hueMax, int saturationMin, int saturationMax, int valueMin, int valueMax, bool reverse, int backgroundImageResourceId) {
    this->hueMin = hueMin;
    this->hueMax = hueMax;
    this->saturationMin = saturationMin;
    this->saturationMax = saturationMax;
    this->valueMin = valueMin;
    this->valueMax = valueMax;
    this->reverse = reverse;
    this->backgroundImageResourceId = backgroundImageResourceId;
}

Chromakey::~Chromakey() {

}

void Chromakey::operator()() {

}

void Chromakey::operator()(cv::Mat* mat) {
    cv::Mat hsv;
    cvtColor(*mat, hsv, cv::COLOR_BGR2HSV);
    cv::Mat mask;
    cv::inRange(hsv, cv::Scalar(hueMin, saturationMin, valueMin), cv::Scalar(hueMax, saturationMax, valueMax), mask);
    if (reverse) mask = ~mask;

    cv::Mat background = ((cv::Mat*)EveProject::getInstance()->getImage(backgroundImageResourceId)->getResource())->clone();
    cv::resize(background, background, cv::Size(mat->cols, mat->rows));

    copyTo(*mat, background, mask);
}