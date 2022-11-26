#pragma once
#include "Command.h"
#include "EveProject.h"

class Chromakey : public Command
{
private:
    int hueMin, hueMax;
    int saturationMin, saturationMax;
    int valueMin, valueMax;
    bool reverse;
    int backgroundImageResourceId;
public:
    Chromakey(bool addToList, int hueMin, int hueMax, int saturationMin, int saturationMax, int valueMin, int valueMax, bool reverse, int backgroundImageResourceId);
    ~Chromakey();

    void operator()();
    void operator()(cv::Mat* mat);
    void operator()(cv::Mat* mat, Image* image);
};


