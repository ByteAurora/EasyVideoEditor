#pragma once

#include <iostream>

class Resource
{
public:
    enum ResourceType {
        IMAGE, VIDEO
    };
protected:
    int resourceId;
    ResourceType resourceType;
    std::string resourcePath;
public:
    Resource();
    ~Resource();

    virtual bool loadResource() = 0;
    virtual void* getResource() = 0;
public:
    void setResourceId(int resourceId);
    void setResourceType(ResourceType resourceType);
    void setResourcePath(std::string resourcePath);

    int getResourceId();
    ResourceType getResourceType();
    std::string getResourcePath();
};

