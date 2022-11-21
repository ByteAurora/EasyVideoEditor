#include "CutVideo.h"

CutVideo::CutVideo() {
	start_frame = 0;
	end_frame = 0;
}

CutVideo::CutVideo(int start_frame, int end_frame) {
	this->start_frame = start_frame;
	this->end_frame = end_frame;
}

CutVideo::~CutVideo(){}
