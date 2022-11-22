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
	int start_frame;
	int end_frame;

public:
	AddImage(bool addToList, Image* image, int x, int y, int width, int height, int start_frame, int end_frame); // addToList 사용여부 frame list 를 조절하는지 여부, true로 무조건 넘겨주기 addimage, add subtitle
	~AddImage();

	void operator()();
	void operator()(cv::Mat* mat);
};

