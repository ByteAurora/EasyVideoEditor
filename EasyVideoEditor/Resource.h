#pragma once

#include <iostream>

/*
* @version  v1.0.0
* @author   Sohn Young Jin
* @since    v1.0.0
*
* The EveProject class is a class of the singleton pattern that is created when the program is executed.
* All frame objects currently being modified in the program and resource(videos, images) being used are managed in a list.
*/
class Resource
{
public:
    // An enumeration of the type of resource.
    enum ResourceType {
        IMAGE, VIDEO
    };
protected:
    // The index of that resource in EveProject.videoList or EveProject.imageList.
    int resourceId;

    // Resource type(ResourceType.IMAGE or ResourceType.VIDEO).
    ResourceType resourceType;

    // Resource path.
    std::string resourcePath;
public:
    // Default constructor.
    Resource();

    // Default destructor.
    ~Resource();

    // A pure virtual function that must implement the resource loading process.
    virtual bool loadResource() = 0;

    // A pure virtual function that must be implement the process of returning a resource.
    // The return value is void*, and it is used after converting to Video* or Image* depending on the type of resource.
    virtual void* getResource() = 0;
public:
    // Resource ID setter.
    void setResourceId(int resourceId);
    // Resource ID getter.
    int getResourceId();

    // Resource type setter.
    void setResourceType(Resource::ResourceType resourceType);
    // Resource type getter.
    Resource::ResourceType getResourceType();

    // Resource path setter.
    void setResourcePath(std::string resourcePath);
    // Resource path getter.
    std::string getResourcePath();
};

