#include "AddSubtitle.h"


AddSubtitle::AddSubtitle(bool addToList, QString subtitle, QString font, int option, int size, int r_color, int g_color, int b_color) : Command(addToList) {
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
	QImage qimage = UsefulFunction::matToQImage(mat);
	QRect subtitleArea;
	QFont qfont(font, size, QFont::Normal);
	qpainter.begin(&qimage);
	qpainter.setPen(QPen(QColor(r_color, g_color, b_color)));
	qpainter.setFont(qfont);

	QFontMetrics qfontMetrics(qfont);
	int height = qfontMetrics.height();
	if (option == 1) { // Top
		subtitleArea.setLeft(0);
		subtitleArea.setRight(mat->cols);
		subtitleArea.setTop(16);
		subtitleArea.setHeight(height);
	} else if (option == 2) {// Middle
		subtitleArea.setLeft(0);
		subtitleArea.setRight(mat->cols);
		subtitleArea.setHeight(mat->rows);
	} else if (option == 3) {// Bottom
		subtitleArea.setLeft(0);
		subtitleArea.setRight(mat->cols);
		subtitleArea.setTop(mat->rows - height - 16);
		subtitleArea.setHeight(height);
	}
	qpainter.drawText(subtitleArea, Qt::AlignCenter, subtitle);
	qpainter.end();
	cv::Mat temp = UsefulFunction::QImageToMat(&qimage);
	temp.copyTo(*mat);
}