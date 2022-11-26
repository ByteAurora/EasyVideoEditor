#include "AddImage.h"


AddImage::AddImage(bool addToList, Image* image, int x, int y, int width, int height) : Command(addToList) {
	this->image = image;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

AddImage::~AddImage() {
}

void AddImage::operator()() {

}

void AddImage::operator()(cv::Mat* mat) {
	cv::Mat cloneImg = ((cv::Mat *)image->getResource())->clone();
	cv::resize(cloneImg, cloneImg, cv::Size(width,height));
	cloneImg.copyTo((*mat)(cv::Rect(x, y, width, height)));	
}

void AddImage::operator()(cv::Mat* mat, Image* image) {
	cv::Mat cloneImg = ((cv::Mat*)image->getResource())->clone();
	cv::resize(cloneImg, cloneImg, cv::Size(width, height));
	cloneImg.copyTo((*mat)(cv::Rect(x, y, width, height)));
}