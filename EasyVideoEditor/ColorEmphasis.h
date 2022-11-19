#pragma once
#include "Command.h"

class ColorEmphasis : public Command
{
private:
    int redChangeValue;
    int greenChangeValue;
    int blueChangeValue;
public:
    ColorEmphasis();
    ColorEmphasis(int red, int green, int blue);
    ~ColorEmphasis();

    virtual void operator()();
    virtual void operator()(cv::Mat* mat);
};

