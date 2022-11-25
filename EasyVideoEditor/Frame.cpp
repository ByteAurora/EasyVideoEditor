#include "Frame.h"
#include "UsefulFunction.h"

Frame::Frame() {
    sourceId = 0;
    sourceFrameIndex = 0;
}

Frame::Frame(int sourceId, int sourceFrameIndex) {
    this->sourceId = sourceId;
    this->sourceFrameIndex = sourceFrameIndex;
}

Frame::~Frame() {

}

void Frame::copyTo(Frame* frame) {
    frame->sourceId = sourceId;
    frame->sourceFrameIndex = sourceFrameIndex;
    frame->commandList = commandList;
}

void Frame::setFrameInfo(int sourceId, int sourceFrameIndex) {
    this->sourceId = sourceId;
    this->sourceFrameIndex = sourceFrameIndex;
}

Command* Frame::getCommand(int index) {
    std::list<Command*>::iterator it = commandList.begin();
    std::advance(it, index);
    return *it;
}

void Frame::addCommand(Command* command) {
    commandList.push_back(command);
}

void Frame::removeAllCommand() {
    commandList.clear();
}

void Frame::removeLastCommand() {
    commandList.pop_back();
}

void Frame::removeCommand(int index) {
    std::list<Command*>::iterator it = commandList.begin();
    std::advance(it, index);
    delete* it;
    commandList.erase(it);
}

void Frame::removeCommand(Command* command) {
    commandList.remove(command);
}

Frame* Frame::getRealFrameData(int beforeSourceId, int beforeSourceFrameIndex, cv::Mat* mat, bool moveEvent) {
    cv::VideoCapture* video = ((cv::VideoCapture*)(EveProject::getInstance()->getVideo(sourceId)->getResource()));
    
    if (moveEvent && (beforeSourceId != sourceId || (beforeSourceId == sourceId && beforeSourceFrameIndex + 1 != sourceFrameIndex))) {
        video->set(cv::CAP_PROP_POS_FRAMES, sourceFrameIndex);
    }

    (*video) >> (*mat);

    return this;
}

Frame* Frame::getCommandAppliedFrameData(int beforeSourceId, int beforeSourceFrameIndex, cv::Mat* mat, bool moveEvent) {
    cv::VideoCapture* video = ((cv::VideoCapture*)(EveProject::getInstance()->getVideo(sourceId)->getResource()));

    if (moveEvent && (beforeSourceId != sourceId || (beforeSourceId == sourceId && beforeSourceFrameIndex + 1 != sourceFrameIndex))) {
        video->set(cv::CAP_PROP_POS_FRAMES, sourceFrameIndex);
        (*video) >> (*mat);
        // If use this codes, frame position error not occured but performance would be slow.
        /*if (video->get(cv::CAP_PROP_POS_FRAMES) != sourceFrameIndex || mat->cols <= 0) {
            video->set(cv::CAP_PROP_POS_FRAMES, 0);
            for (int loop = 0; loop < sourceFrameIndex; loop++) {
                video->grab();
            }
            (*video) >> (*mat);
        }*/
    }
    else {
        (*video) >> (*mat);
    }

    for (std::list<Command*>::iterator it = commandList.begin(); it != commandList.end(); it++) { 
        (*(*it))(mat);
    }

    return this;
}

void Frame::setSourceId(int sourceId) {
    this->sourceId = sourceId;
}

void Frame::setSourceFrameIndex(int sourceFrameIndex) {
    this->sourceFrameIndex = sourceFrameIndex;
}

void Frame::setCommandList(std::list<Command*> commandList) {
    this->commandList = commandList;
}

int Frame::getSourceId() {
    return sourceId;
}

int Frame::getSourceFrameIndex() {
    return sourceFrameIndex;
}

std::list<Command*>* Frame::getCommandList() {
    return &commandList;
}