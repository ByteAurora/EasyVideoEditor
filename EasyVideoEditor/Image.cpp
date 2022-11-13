#include "Image.h"

Image::Image() {

}

Image::~Image() {

}

bool Image::loadResource() {
    mat = cv::imread(resourcePath, cv::IMREAD_COLOR);
    return !mat.empty();
}

void* Image::getResource(){
    return &mat;
}