#pragma once
#include "Command.h"

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

