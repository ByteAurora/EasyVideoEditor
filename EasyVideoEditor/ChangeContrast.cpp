#include "ChangeContrast.h"

ChangeContrast::ChangeContrast(bool addToList, int contrast) : Command(addToList){
    this->contrast = contrast;
}

ChangeContrast::~ChangeContrast() {

}

void ChangeContrast::operator()() {

}

void ChangeContrast::operator()(cv::Mat* mat) {
    cv::Mat lab;
    cv::cvtColor(*mat, lab, cv::COLOR_BGR2Lab);
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE((contrast / 20.f) + 0.1f, cv::Size(8, 8));
    cv::Mat labSplit[3];
    cv::split(lab, labSplit);
    clahe->apply(labSplit[0], labSplit[0]);
    cv::merge(labSplit, 3, lab);
    cvtColor(lab, *mat, cv::COLOR_Lab2BGR);
}