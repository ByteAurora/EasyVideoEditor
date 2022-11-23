#include "Frame.h"

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

void Frame::getRealFrameData(cv::Mat* mat, bool moveEvent) {
    cv::VideoCapture* video = ((cv::VideoCapture*)(EveProject::getInstance()->getVideo(sourceId)->getResource()));
    if(moveEvent) video->set(cv::CAP_PROP_POS_FRAMES, sourceFrameIndex);
    (*video) >> (*mat);
}

void Frame::getCommandAppliedFrameData(cv::Mat* mat, bool moveEvent) {
    cv::VideoCapture* video = ((cv::VideoCapture*)(EveProject::getInstance()->getVideo(sourceId)->getResource()));
    if (moveEvent || sourceFrameIndex != video->get(cv::CAP_PROP_POS_FRAMES)) video->set(cv::CAP_PROP_POS_FRAMES, sourceFrameIndex);
    
    (*video) >> (*mat);

    for (std::list<Command*>::iterator it = commandList.begin(); it != commandList.end(); it++) { 
        (*(*it))(mat); // ¸î¹øÂ° command
    }
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