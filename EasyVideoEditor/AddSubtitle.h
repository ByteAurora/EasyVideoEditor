#pragma once
#include "Command.h"
#include <Qimage>
#include <QPainter>
#include <QColor>
#include "UsefulFunction.h"

class AddSubtitle : public Command
{
private:
	QString subtitle;
	QString font;
	int option;
	int size;
	int r_color;
	int g_color;
	int b_color;
	QPainter qpainter;

public:
	AddSubtitle(bool addToList, QString subtitle, QString font, int option, int size, int r_color, int g_color, int b_color);
	~AddSubtitle();

	void operator()();
	void operator()(cv::Mat* mat);
};

