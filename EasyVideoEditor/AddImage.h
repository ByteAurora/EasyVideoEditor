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
	AddImage(bool addToList, Image* image, int x, int y, int width, int height, int start_frame, int end_frame); // addToList ��뿩�� frame list �� �����ϴ��� ����, true�� ������ �Ѱ��ֱ� addimage, add subtitle
	~AddImage();

	void operator()();
	void operator()(cv::Mat* mat);
};

