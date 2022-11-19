#pragma once
#include "Command.h"

class Filter : public Command
{
public:
    enum FilterType {
        NONE, SPRING, SUMMER, AUTUMN, WINTER, OCEAN, WARM, COOL
    };
private:
    FilterType filterType;
    int clarity;
public:
    Filter();
    Filter(int clarity);
    Filter(Filter::FilterType filterType);
    Filter(int clarity, Filter::FilterType filterType);
    ~Filter();

    virtual void operator()();
    virtual void operator()(cv::Mat* mat);
};

