#pragma once
#include "Command.h"

class Transition : public Command
{
private:
    cv::Mat black;
    double weight;
public:
    Transition(bool addToList, double weight);
    ~Transition();

    void operator()();
    void operator()(cv::Mat* mat);
};

