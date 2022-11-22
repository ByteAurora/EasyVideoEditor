#pragma once

#include <qthread.h>
#include <opencv2/opencv.hpp>
#include "EasyVideoEditor.h"
#include "EveProject.h"
#include "Widgets.h"
#include "UsefulFunction.h"

class EasyVideoEditor;

class PlayVideo : public QThread
{
    Q_OBJECT
public:
    explicit PlayVideo(QObject* parent = 0);
private:
    void run();
};

