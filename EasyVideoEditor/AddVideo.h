#pragma once
#include "Command.h"
class AddVideo : public Command
{
private:
	int start_time;
	int end_time;
public:
	AddVideo(bool addToList, int start_time, int end_time);
	~AddVideo();
};

