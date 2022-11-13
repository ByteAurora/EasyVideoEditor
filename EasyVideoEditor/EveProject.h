#pragma once

#include <string>
#include <list>
#include "Command.h"
#include "Resource.h"
#include "Image.h"
#include "Video.h"
#include "Frame.h"

class EveProject
{
private:
    std::list<Video*> videoList;
    std::list<Image*> imageList;
    std::list<Frame*> frameList;
    int currentFrameNumber;
public:
    EveProject();
    ~EveProject();

    void addVideo(Video* video);
    Video* getVideo(int index);
    void addImage(Image* image);
    Image* getImage(int index);
    void addFrame(Frame* frame);
    Frame* getFrame(int index);
    void removeFrame(int index);
    void removeFrames(int index, int count);
    Frame* getCurrentFrame();
    Frame* getCurrentFrameAndUpdate();
    int getBaseFps();
    int getBaseDelay();
    int getBaseFrameCount();
    int getBaseWidth();
    int getBaseHeight();
    bool forward5Seconds();
    bool backward5Seconds();
public:
    void setFrameList(std::list<Frame*> frameList);
    std::list<Frame*>* getFrameList();
    void setCurrentFrameNumber(int frameNumber);
    int getCurrentFrameNumber();
};

