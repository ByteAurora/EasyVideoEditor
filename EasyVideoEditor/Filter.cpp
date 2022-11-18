#include "Filter.h"

Filter::Filter() {
    clarity = 50;
    filterType = FilterType::NONE;
}

Filter::Filter(int clarity) {
    this->clarity = clarity;
    filterType = FilterType::NONE;
}

Filter::Filter(Filter::FilterType filterType) {
    clarity = 50;
    this->filterType = filterType;
}


Filter::Filter(int contrast, Filter::FilterType filterType) {
    this->clarity = contrast;
    this->filterType = filterType;
}

Filter::~Filter() {

}

void Filter::operator()() {

}

void Filter::operator()(cv::Mat* mat) {
    if (clarity < 50) {
        cv::GaussianBlur(*mat, *mat, cv::Size(), ((double)50 - clarity) / 20.0f);
    }
    else if(clarity > 50) {
        cv::Mat blurred;
        cv::GaussianBlur(*mat, blurred, cv::Size(), ((double)clarity - 50) / 20.f);
        *mat = 2.0f * (*mat) - 1.0f * blurred;
    }
}