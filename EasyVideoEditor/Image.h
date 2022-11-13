#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Resource.h"

class Image : public Resource
{
private:
    cv::Mat mat;
public:
    Image();
    ~Image();

    virtual bool loadResource();
    virtual void* getResource();
};

