#pragma once
#include "Command.h"

class Filter : public Command
{
public:
    enum FilterType {
        NONE, GRAY, WARM, COOL, BRIGHT
    };
private:
    FilterType filterType;
    int clarity;
public:
    Filter(bool addToList, int clarity, Filter::FilterType filterType);
    ~Filter();

    void operator()();
    void operator()(cv::Mat* mat);
};

