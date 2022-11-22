#pragma once
#include "Command.h"

class AddImage : public Command
{
private:
	std::string imagePath;
	int x;
	int y;
	int width;
	int height;
	int start_frame;
	int end_frame;

public:
	AddImage();
	AddImage(std::string imagePath, int x, int y, int width, int height, int start_frame, int end_frame);
	~AddImage();

	virtual void operator()();
	virtual void operator()(cv::Mat* mat);
};

