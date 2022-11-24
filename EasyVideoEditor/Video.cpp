#include "Video.h"

Video::Video() {
    fps = 0;
    delay = 0;
    width = 0;
    height = 0;
    frameCount = 0;
    resourceType = VIDEO;
    resourceId = 0;
    resourcePath = "";
}

Video::Video(int resourceId) {
    fps = 0;
    delay = 0;
    width = 0;
    height = 0;
    frameCount = 0;
    resourceType = VIDEO;
    this->resourceId = resourceId;
    this->resourcePath = "";
}

Video::Video(std::string resourcePath) {
    fps = 0;
    delay = 0;
    width = 0;
    height = 0;
    frameCount = 0;
    resourceType = VIDEO;
    resourceId = 0;
    this->resourcePath = resourcePath;
}

Video::Video(int resourceId, std::string resourcePath) {
    fps = 0;
    delay = 0;
    width = 0;
    height = 0;
    frameCount = 0;
    resourceType = VIDEO;
    this->resourceId = resourceId;
    this->resourcePath = resourcePath;
}

Video::~Video() {

}

bool Video::loadResource() {
    if (video.open(resourcePath, cv::CAP_ANY)) {
        width = cvRound(video.get(cv::CAP_PROP_FRAME_WIDTH));
        height = cvRound(video.get(cv::CAP_PROP_FRAME_HEIGHT));
        frameCount = cvRound(video.get(cv::CAP_PROP_FRAME_COUNT));
        fps = video.get(cv::CAP_PROP_FPS);
        delay = cvRound(1000 / fps);

        return true;
    }
    return false;
}

void* Video::getResource() {
    return &video;
}

void Video::releaseResource() {
    if (video.isOpened()) {
        video.release();
    }
}

void Video::setFps(double fps) {
    this->fps = fps;
}

double Video::getFps() {
    return fps;
}

void Video::setDelay(int delay) {
    this->delay = delay;
}

int Video::getDelay() {
    return delay;
}

void Video::setWidth(int width) {
    this->width = width;
}

int Video::getWidth() {
    return width;
}

void Video::setHeight(int height) {
    this->height = height;
}

int Video::getHeight() {
    return height;
}

void Video::setFrameCount(int frameCount) {
    this->frameCount = frameCount;
}

int Video::getFrameCount() {
    return frameCount;
}