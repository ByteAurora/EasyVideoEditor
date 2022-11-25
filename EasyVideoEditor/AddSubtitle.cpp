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
void AddSubtitle::operator()(cv::Mat* mat) {

	double fontScale = size * 0.1;
	cv::Size sizeText = cv::getTextSize(subtitle, font, fontScale,1,0);
	cv::Size sizeImg = (*mat).size();
	cv::Point org;

	if (option == 1) // Top
		org = cv::Point((sizeImg.width - sizeText.width) / 2, sizeImg.height - (sizeImg.height - sizeText.height));
	else if (option == 2) // Middle
		org = cv::Point((sizeImg.width - sizeText.width) / 2, (sizeImg.height - sizeText.height) / 2);
	else if (option == 3) // Bottom
		org = cv::Point((sizeImg.width - sizeText.width) / 2, (sizeImg.height - sizeText.height));

	cv::putText(*mat, subtitle, org, font, fontScale, cv::Scalar(b_color, g_color, r_color), 1);
}