#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <QString>
#include <QFile>
#include "Resource.h"

/*
* @version  v1.0.0
* @author   Sohn Young Jin
* @since    v1.0.0
*
* The Image class is a class that inherits Resource class.
* Stores information about image resources used in EveProject.
*/
class Image : public Resource
{
private:
    // Mat to use image in opencv.
    cv::Mat image;
public:
    // Default constructor.
    Image();

    // Custom constructor.
    Image(int resourceId);
    Image(std::string resourcePath);
    Image(int resourceId, std::string resourcePath);

    // Default destructor.
    ~Image();

    // A pure virtual function that must implement the resource loading process.
    virtual bool loadResource();

    // A pure virtual function that must be implement the process of returning a resource.
    // The return value is void*, and it is used after converting to Video* or Image* depending on the type of resource.
    virtual void* getResource();
};

