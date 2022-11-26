#pragma once
#include <qobject.h>
#include "EasyVideoEditor.h"

class VideoProgressEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit VideoProgressEventFilter(QLabel* videoFrame, QSlider* videoProgress, QLabel* currentPlayTime, QObject* parent = nullptr);
signals:
public:
    bool eventFilter(QObject* obj, QEvent* e);
private:
    QSlider* videoProgress;
    QLabel* currentPlayTime;
    QLabel* videoFrame;
};

