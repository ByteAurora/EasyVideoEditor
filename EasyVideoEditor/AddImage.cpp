#include "AddImage.h"


AddImage::AddImage(bool addToList, Image* image, int x, int y, int width, int height, int start_frame, int end_frame){
	this->image = image;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->start_frame = start_frame;
	this->end_frame = end_frame;
}

AddImage::~AddImage() {
}

void AddImage::operator()() {

}

void AddImage::operator()(cv::Mat* mat) {
	cv::Mat cloneImg = ((cv::Mat *)image->getResource())->clone();
	cv::resize(cloneImg, cloneImg, cv::Size(width,height));
	(*mat)(cv::Rect(x, y, width, height)) = 0;
	(*mat)(cv::Rect(x, y, width, height)) += cloneImg;	
}

