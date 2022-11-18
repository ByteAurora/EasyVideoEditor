#include "ColorEmphasis.h"

ColorEmphasis::ColorEmphasis() {
    redChangeValue = 0;
    greenChangeValue = 0;
    blueChangeValue = 0;
}

ColorEmphasis::ColorEmphasis(int redChangeValue, int greenChangeValue, int blueChangeValue) {
    this->redChangeValue = redChangeValue;
    this->greenChangeValue = greenChangeValue;
    this->blueChangeValue = blueChangeValue;
}

void ColorEmphasis::operator()() {

}

void ColorEmphasis::operator()(cv::Mat* mat) {
    (*mat) += cv::Scalar(blueChangeValue, greenChangeValue, redChangeValue);
}