#pragma once
#include "Command.h"
#include "EveProject.h"

class Chromaky : public Command
{
private:
    int hueMin, hueMax;
    int saturationMin, saturationMax;
    int valueMin, valueMax;
    bool reverse;
    int backgroundImageResourceId;
public:
    Chromaky();
    Chromaky(int hueMin, int hueMax, int saturationMin, int saturationMax, int valueMin, int valueMax, bool reverse, int backgroundImageResourceId);
    ~Chromaky();

    virtual void operator()();
    virtual void operator()(cv::Mat* mat);
};


