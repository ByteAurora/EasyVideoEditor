#pragma once
#include "Command.h"
class CutVideo : public Command
{
private:
	int start_frame;
	int end_frame;

public:
	CutVideo(bool addToList, int start_frame, int end_frame);
	~CutVideo();
};

