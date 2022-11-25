#include "EveProject.h"

EveProject* EveProject::instance = NULL;

EveProject::EveProject() {
    currentFrameNumber = -1;
}

EveProject::~EveProject() {

}

EveProject* EveProject::getInstance() {
    if (instance == NULL) {
        instance = new EveProject();
    }

    return instance;
}

void EveProject::clear(QMainWindow* window) {
    for (int loop = 0; loop < videoList.size(); loop++) {
        videoList.at(loop)->releaseResource();
        free(videoList.at(loop));
    }
    videoList.clear();

    for (int loop = 0; loop < imageList.size(); loop++) {
        free(imageList.at(loop));
    }
    imageList.clear();

    for (int loop = 0; loop < Command::commandList.size(); loop++) {
        free(Command::commandList.at(loop));
    }
    Command::commandList.clear();

    for (int loop = 0; loop < frameList.size(); loop++) {
        free(frameList.at(loop));
    }
    frameList.clear();

    currentFrameNumber = -1;
}

void EveProject::addVideo(Video* video) {
    if (currentFrameNumber == -1) { currentFrameNumber = 0; }
    videoList.push_back(video);
    video->setResourceId(videoList.size() - 1);
    video->loadResource();
}

Video* EveProject::getVideo(int index) {
    return videoList.at(index);
}

void EveProject::addImage(Image* image) {
    imageList.push_back(image);
    image->setResourceId(imageList.size() - 1);
    image->loadResource();
}

Image* EveProject::getImage(int index) {
    return imageList.at(index);
}

void EveProject::addFrame(Frame* frame) {
    frameList.push_back(frame);
}

void EveProject::addFrame(Frame* frame, int index) {
    frameList.insert(frameList.begin() + index, frame);
}

void EveProject::addFrames(std::vector<Frame*> frames, int index) {
    frameList.insert(frameList.begin() + index + 1, frames.begin(), frames.end());
}

Frame* EveProject::getFrameByIndex(int index) {
    return frameList.at(index);
}

Frame* EveProject::getFrameByTime(int millisecond) {
    return frameList.at(millisecond / getBaseDelay());
}

int EveProject::getFrameIndex(Frame* frame) {
    std::vector<Frame*>::iterator it = std::find(frameList.begin(), frameList.end(), frame);
    if (it != frameList.end()) return it - frameList.begin();
    else return -1;
}

int EveProject::getFrameIndex(int millisecond) {
    return millisecond / getBaseDelay();
}

int EveProject::getFrameTime(Frame* frame) {
    return getFrameIndex(frame) * getBaseFps();
}

int EveProject::getFrameTime(int index) {
    return index * getBaseDelay();
}

int EveProject::removeFrame(int index) {
    frameList.erase(frameList.begin() + index);
    return frameList.size();
}

int EveProject::removeFrames(int index, int count) {
    std::vector<Frame*>::iterator lastIndex = frameList.begin() + index + count;
    if (frameList.begin() + index + count > frameList.end()) lastIndex = frameList.end();
    frameList.erase(frameList.begin() + index, lastIndex);
    return frameList.size();
}

Frame* EveProject::getCurrentFrame() {
    return frameList.at(currentFrameNumber);
}

Frame* EveProject::getCurrentFrameAndUpdate() {
    return frameList.at(currentFrameNumber++);
}

double EveProject::getBaseFps() {
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
    if (currentFrameNumber - 1 < 0) {
        return false;
    }

    currentFrameNumber--;
    return true;
}

bool EveProject::backward1Frame() {
    if (currentFrameNumber + 1 >= frameList.size()) {
        return false;
    }

    currentFrameNumber++;
    return true;
}

bool EveProject::forward5Seconds() {
    if (currentFrameNumber - getBaseFps() * 5 < 0) {
        currentFrameNumber = 0;
        return false;
    }

    currentFrameNumber -= getBaseFps() * 5;
    return true;
}

bool EveProject::backward5Seconds() {
    if (currentFrameNumber + getBaseFps() * 5 >= frameList.size()) {
        currentFrameNumber = frameList.size() - 1;
        return false;
    }

    currentFrameNumber += getBaseFps() * 5;
    return true;
}

void EveProject::setFrameList(std::vector<Frame*> frameList) {
    this->frameList = frameList;
}

std::vector<Frame*>* EveProject::getFrameList() {
    return &frameList;
}

std::vector<Video*>* EveProject::getVideoList() {
    return &videoList;
}

std::vector<Image*>* EveProject::getImageList() {
    return &imageList;
}

void EveProject::setCurrentFrameNumber(int frameNumber) {
    currentFrameNumber = frameNumber;
}

int EveProject::getCurrentFrameNumber() {
    return currentFrameNumber;
}