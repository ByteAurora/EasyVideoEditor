#include "ChangeBrightness.h"

ChangeBrightness::ChangeBrightness() {
    brightness = 50;
}

ChangeBrightness::ChangeBrightness(int brightness) {
    this->brightness = brightness;
}

ChangeBrightness::~ChangeBrightness() {

}

void ChangeBrightness::operator()() {

}

void ChangeBrightness::operator()(cv::Mat* mat) {
    int changeValue = 5.1f * (brightness - 50);
    (*mat) += cv::Scalar(changeValue, changeValue, changeValue);
}