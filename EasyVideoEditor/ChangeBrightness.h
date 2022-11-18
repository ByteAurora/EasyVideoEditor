#pragma once
#include "Command.h"
#include <opencv2/opencv.hpp>

class ChangeBrightness : public Command {
private:
    int brightness;
public:
    ChangeBrightness();
    ChangeBrightness(int brightness);
    ~ChangeBrightness();

    virtual void operator()();
    virtual void operator()(cv::Mat* mat);
};

