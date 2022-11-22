#pragma once
#include "Command.h"

class ColorEmphasis : public Command
{
private:
    int redChangeValue;
    int greenChangeValue;
    int blueChangeValue;
public:
    ColorEmphasis(bool addToList, int red, int green, int blue);
    ~ColorEmphasis();

    void operator()();
    void operator()(cv::Mat* mat);
};

