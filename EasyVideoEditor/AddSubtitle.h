#pragma once
#include "Command.h"

class AddSubtitle : public Command
{
private:
	std::string subtitle;
	std::string font;
	int option;
	int size;
	int r_color;
	int g_color;
	int b_color;
	int start_frame;
	int end_frame;

public:
};

