#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Resource.h"

/*
* @version  v1.0.0
* @author   Sohn Young Jin
* @since    v1.0.0
*
* The Video class is a class that inherits Resource class.
* Stores information about video resources used in EveProject.
*/
class Video : public Resource
{
private:
    // VideoCapture to control video with opencv.
    cv::VideoCapture video;

    // Video's frames per seconds.
    int fps;

    // Delay between frames.
    int delay;

    // Width of frame.
    int width;
    
    // Height of frame.
    int height;

    // Total frame count in video.
    int frameCount;
public:
    // Default constructor.
    Video();

    // Custom constructor.
    Video(int resourceId);
    Video(std::string resourcePath);
    Video(int resourceId, std::string resourcePath);

    // Default destructor.
    ~Video();

    // A pure virtual function that must implement the resource loading process.
    virtual bool loadResource();

    // A pure virtual function that must be implement the process of returning a resource.
    // The return value is void*, and it is used after converting to Video* or Image* depending on the type of resource.
    virtual void* getResource();

    // Close opened video.
    void releaseResource();

    // Fps setter.
    void setFps(int fps);
    // Fps getter.
    int getFps();

    // Delay setter.
    void setDelay(int delay);
    // Delay getter.
    int getDelay();

    // Width setter.
    void setWidth(int width);
    // Width getter.
    int getWidth();

    // Height setter.
    void setHeight(int height);
    // Height getter.
    int getHeight();

    // Frame count setter.
    void setFrameCount(int frameCount);
    // Frame count getter.
    int getFrameCount();
};

