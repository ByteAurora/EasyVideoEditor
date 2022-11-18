#pragma once
#include "Command.h"
#include <opencv2/opencv.hpp>

class ChangeContrast : public Command
{
private:
    int contrast;
public:
    ChangeContrast();
    ChangeContrast(int contrast);
    ~ChangeContrast();

    virtual void operator()();
    virtual void operator()(cv::Mat* mat);
};

