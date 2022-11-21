#include "AddSubtitle.h"

AddSubtitle::AddSubtitle() {
	subtitle = "";
	font = 0;
	option = 0;
	size = 0;
	r_color = 0;
	g_color = 0;
	b_color = 0;
	start_frame = 0;
	end_frame = 0;
}

AddSubtitle::AddSubtitle(std::string subtitle, int font, int option, int size, int r_color, int g_color, int b_color, int start_frame, int end_frame) {
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