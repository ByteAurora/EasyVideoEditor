#include "AddVideo.h"

AddVideo::AddVideo() {
	start_time = 0;
	end_time = 0;
}

AddVideo::AddVideo(int start_time, int end_time) {
	this->start_time = start_time;
	this->end_time = end_time;
}

AddVideo::~AddVideo(){}