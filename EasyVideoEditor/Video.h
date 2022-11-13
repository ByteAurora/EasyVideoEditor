#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Resource.h"

class Video : public Resource
{
private:
    cv::VideoCapture video;
    int fps;
    int delay;
    int width;
    int height;
    int frameCount;
public:
    Video();
    ~Video();

    virtual bool loadResource();
    virtual void* getResource();
    void setFps(int fps);
    int getFps();
    void setDelay(int delay);
    int getDelay();
    void setWidth(int width);
    int getWidth();
    void setHeight(int height);
    int getHeight();
    void setFrameCount(int frameCount);
    int getFrameCount();
};

