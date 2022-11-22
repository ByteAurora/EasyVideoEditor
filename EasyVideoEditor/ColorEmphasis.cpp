#include "ColorEmphasis.h"

ColorEmphasis::ColorEmphasis(bool addToList, int redChangeValue, int greenChangeValue, int blueChangeValue) : Command(addToList){
    this->redChangeValue = redChangeValue;
    this->greenChangeValue = greenChangeValue;
    this->blueChangeValue = blueChangeValue;
}

ColorEmphasis::~ColorEmphasis() {

}

void ColorEmphasis::operator()() {

}

void ColorEmphasis::operator()(cv::Mat* mat) {
    (*mat) += cv::Scalar(blueChangeValue, greenChangeValue, redChangeValue);
}