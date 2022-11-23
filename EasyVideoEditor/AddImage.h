#pragma once
#include "Command.h"
#include "Image.h"

class AddImage : public Command
{
private:
	Image* image;
	int x;
	int y;
	int width;
	int height;

public:
	AddImage(bool addToList, Image* image, int x, int y, int width, int height);
	~AddImage();

	void operator()();
	void operator()(cv::Mat* mat);
};

