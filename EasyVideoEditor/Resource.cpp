#include "Resource.h"

Resource::Resource() {

}

Resource::~Resource() {

}

void Resource::setResourceId(int resourceId) {
    this->resourceId = resourceId;
}

void Resource::setResourceType(Resource::ResourceType resourceType) {
    this->resourceType = resourceType;
}

void Resource::setResourcePath(std::string resourcePath) {
    this->resourcePath = resourcePath;
}

int Resource::getResourceId() {
    return resourceId;
}

Resource::ResourceType Resource::getResourceType() {
    return resourceType;
}

std::string Resource::getResourcePath() {
    return resourcePath;
}