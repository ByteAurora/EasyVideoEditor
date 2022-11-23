#pragma once
#include "Command.h"

class AddSubtitle : public Command
{
private:
	std::string subtitle;
	int font;
	int option;
	int size;
	int r_color;
	int g_color;
	int b_color;

public:
	AddSubtitle(bool addToList, std::string subtitle, int font, int option, int size, int r_color, int g_color, int b_color);
	~AddSubtitle();

	void operator()();
	void operator()(cv::Mat* mat);
};

