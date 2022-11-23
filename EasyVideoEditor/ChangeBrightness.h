#pragma once
#include "Command.h"

class ChangeBrightness : public Command {
private:
    int brightness;
public:
    ChangeBrightness(bool addToList, int brightness);
    ~ChangeBrightness();

    void operator()();
    void operator()(cv::Mat* mat);
};

