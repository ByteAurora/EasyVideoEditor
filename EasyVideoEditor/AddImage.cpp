#include "AddImage.h"

AddImage::AddImage() {
	imagePath = "";
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	start_frame = 0;
	end_frame = 0;
}

AddImage::AddImage(std::string imagePath, int x, int y, int width, int height, int start_frame, int end_frame){
	this->imagePath = imagePath;
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
}

