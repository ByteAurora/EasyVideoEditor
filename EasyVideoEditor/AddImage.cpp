#include "AddImage.h"

AddImage::AddImage() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	start_frame = 0;
	end_frame = 0;
}

AddImage::AddImage(int x, int y, int width, int height, int start_frame, int end_frame){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->start_frame = start_frame;
	this->end_frame = end_frame;
}

AddImage::~AddImage() {
}

