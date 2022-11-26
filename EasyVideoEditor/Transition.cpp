#include "Transition.h"

Transition::Transition(bool addToList, double weight) : Command(addToList) {
    this->weight = weight;
}

Transition::~Transition() {

}

void Transition::operator()() {

}

void Transition::operator()(cv::Mat* mat) {
    black = cv::Mat::zeros(mat->rows, mat->cols, CV_8UC3);
    addWeighted(*mat, weight, black, 1 - weight, 0.0f, *mat);
}