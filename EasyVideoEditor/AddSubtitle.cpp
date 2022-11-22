#include "AddSubtitle.h"


// addToList 사용여부 frame list 를 조절하는지 여부, true로 무조건 넘겨주기 addimage, add subtitle
AddSubtitle::AddSubtitle(bool addToList, std::string subtitle, int font, int option, int size, int r_color, int g_color, int b_color, int start_frame, int end_frame) {
	this->subtitle = subtitle;
	this->font = font;
	this->option = option;
	this->size = size;
	this->r_color = r_color;
	this->g_color = g_color;
	this->b_color = b_color;
	this->start_frame = start_frame;
	this->end_frame = end_frame;
}

AddSubtitle::~AddSubtitle() {}