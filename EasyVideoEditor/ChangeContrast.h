#pragma once
#include "Command.h"

class ChangeContrast : public Command
{
private:
    int contrast;
public:
    ChangeContrast(bool addToList, int contrast);
    ~ChangeContrast();

    void operator()();
    void operator()(cv::Mat* mat);
};

