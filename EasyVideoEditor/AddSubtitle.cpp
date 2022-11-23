#include "AddSubtitle.h"


AddSubtitle::AddSubtitle(bool addToList, std::string subtitle, int font, int option, int size, int r_color, int g_color, int b_color) : Command(addToList) {
	this->subtitle = subtitle;
	this->font = font;
	this->option = option;
	this->size = size;
	this->r_color = r_color;
	this->g_color = g_color;
	this->b_color = b_color;
}

AddSubtitle::~AddSubtitle(){}

void AddSubtitle::operator()() {}
void AddSubtitle::operator()(cv::Mat* mat) {}