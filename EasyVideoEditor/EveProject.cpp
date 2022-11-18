#include "EveProject.h"

EveProject* EveProject::instance = NULL;

EveProject::EveProject() {
    currentFrameNumber = 0;
}

EveProject::~EveProject() {

}

EveProject* EveProject::getInstance() {
    if (instance == NULL) {
        instance = new EveProject();
    }

    return instance;
}

void EveProject::addVideo(Video* video) {
    videoList.push_back(video);
    video->setResourceId(videoList.size() - 1);
}

Video* EveProject::getVideo(int index) {
    return videoList.at(index);
}

void EveProject::addImage(Image* image) {
    imageList.push_back(image);
    image->setResourceId(imageList.size() - 1);
}

Image* EveProject::getImage(int index) {
    return imageList.at(index);
}

void EveProject::addFrame(Frame* frame) {
    frameList.push_back(frame);
}

Frame* EveProject::getFrame(int index) {
    return frameList.at(index);
}

Frame* EveProject::getFrame(long millisecond) {
    return frameList.at(millisecond / getBaseDelay());
}

int EveProject::getFrameIndex(Frame* frame) {
    std::vector<Frame*>::iterator it = std::find(frameList.begin(), frameList.end(), frame);
    if (it != frameList.end()) return it - frameList.begin();
    else return -1;
}

int EveProject::getFrameIndex(long millisecond) {
    return millisecond / getBaseDelay();
}

int EveProject::getFrameTime(Frame* frame) {
    return getFrameIndex(frame) * getBaseFps();
}

int EveProject::getFrameTime(int index) {
    return index * getBaseDelay();
}

void EveProject::removeFrame(int index) {
    frameList.erase(frameList.begin() + index);
}

void EveProject::removeFrames(int index, int count) {
    frameList.erase(frameList.begin() + index, frameList.begin() + index + count);
}

Frame* EveProject::getCurrentFrame() {
    return frameList.at(currentFrameNumber);
}

Frame* EveProject::getCurrentFrameAndUpdate() {
    return frameList.at(currentFrameNumber++);
}

int EveProject::getBaseFps() {
    return videoList.front()->getFps();
}
int EveProject::getBaseDelay() {
    return videoList.front()->getDelay();
}
int EveProject::getBaseFrameCount() {
    return videoList.front()->getFrameCount();
}
int EveProject::getBaseWidth() {
    return videoList.front()->getWidth();
}
int EveProject::getBaseHeight() {
    return videoList.front()->getHeight();
}

bool EveProject::forward1Frame() {
    if (currentFrameNumber + 1 >= frameList.size()) {
        return false;
    }

    currentFrameNumber++;
    return true;
}

bool EveProject::backward1Frame() {
    if (currentFrameNumber - 1 < 0) {
        return false;
    }

    currentFrameNumber--;
    return true;
}

bool EveProject::forward5Seconds() {
    if (currentFrameNumber + getBaseFps() * 5 >= frameList.size()) {
        currentFrameNumber = frameList.size() - 1;
        return false;
    }

    currentFrameNumber += getBaseFps() * 5;
    return true;
}

bool EveProject::backward5Seconds() {
    if (currentFrameNumber - getBaseFps() * 5 < 0) {
        currentFrameNumber = 0;
        return false;
    }

    currentFrameNumber -= getBaseFps() * 5;
    return true;
}

void EveProject::setFrameList(std::vector<Frame*> frameList) {
    this->frameList = frameList;
}

std::vector<Frame*>* EveProject::getFrameList() {
    return &frameList;
}

void EveProject::setCurrentFrameNumber(int frameNumber) {
    currentFrameNumber = frameNumber;
}

int EveProject::getCurrentFrameNumber() {
    return currentFrameNumber;
}