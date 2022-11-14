#include "Image.h"

Image::Image() {
    resourceType = IMAGE;
    resourceId = 0;
    resourcePath = "";
}

Image::Image(int resourceId) {
    this->resourceId = resourceId;
    this->resourcePath = "";
}

Image::Image(std::string resourcePath) {
    resourceType = IMAGE;
    resourceId = 0;
    this->resourcePath = resourcePath;
}

Image::Image(int resourceId, std::string resourcePath) {
    resourceType = IMAGE;
    this->resourceId = resourceId;
    this->resourcePath = resourcePath;
}

Image::~Image() {

}

bool Image::loadResource() {
    image = cv::imread(resourcePath, cv::IMREAD_COLOR);
    return !image.empty();
}

void* Image::getResource(){
    return &image;
}