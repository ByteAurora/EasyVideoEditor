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
    video->setResourceId(videoList.size());
}

Video* EveProject::getVideo(int index) {
    std::list<Video*>::iterator it = videoList.begin();
    std::advance(it, index);
    return *it;
}

void EveProject::addImage(Image* image) {
    imageList.push_back(image);
    image->setResourceId(imageList.size());
}

Image* EveProject::getImage(int index) {
    std::list<Image*>::iterator it = imageList.begin();
    std::advance(it, index);
    return *it;
}

void EveProject::addFrame(Frame* frame) {
    frameList.push_back(frame);
}

Frame* EveProject::getFrame(int index) {
    std::list<Frame*>::iterator it = frameList.begin();
    std::advance(it, index);
    return *it;
}

void EveProject::removeFrame(int index) {
    std::list<Frame*>::iterator it = frameList.begin();
    std::advance(it, index);
    delete* it;
    frameList.erase(it);
}

void EveProject::removeFrames(int index, int count) {
    std::list<Frame*>::iterator it = frameList.begin();
    std::advance(it, index);
    for(int loop = 0; loop < count; loop++){
        delete* it;
        it = frameList.erase(it);
    }
}

Frame* EveProject::getCurrentFrame() {
    std::list<Frame*>::iterator it = frameList.begin();
    std::advance(it, currentFrameNumber);
    return *it;
}

Frame* EveProject::getCurrentFrameAndUpdate() {
    std::list<Frame*>::iterator it = frameList.begin();
    std::advance(it, currentFrameNumber);
    currentFrameNumber++;
    return *it;
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
    if (currentFrameNumber + videoList.front()->getFps() * 5 >= frameList.size()) {
        currentFrameNumber = frameList.size() - 1;
        return false;
    }

    currentFrameNumber += videoList.front()->getFps() * 5;
    return true;
}

bool EveProject::backward5Seconds() {
    if (currentFrameNumber - videoList.front()->getFps() * 5 < 0) {
        currentFrameNumber = 0;
        return false;
    }

    currentFrameNumber -= videoList.front()->getFps() * 5;
    return true;
}

void EveProject::setFrameList(std::list<Frame*> frameList) {
    this->frameList = frameList;
}

std::list<Frame*>* EveProject::getFrameList() {
    return &frameList;
}

void EveProject::setCurrentFrameNumber(int frameNumber) {
    currentFrameNumber = frameNumber;
}

int EveProject::getCurrentFrameNumber() {
    return currentFrameNumber;
}