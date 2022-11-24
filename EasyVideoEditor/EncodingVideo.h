#pragma once
#include <qthread.h>
#include <QMetaObject>
#include <opencv2/opencv.hpp>
#include "EasyVideoEditor.h"
#include "EveProject.h"
#include "Widgets.h"
#include "UsefulFunction.h"

class EasyVideoEditor;

class EncodingVideo : public QThread
{
    Q_OBJECT
public:
    explicit EncodingVideo(QObject* parent, QString encodingType, QString saveFilePath);
private:
    QString encodingType;
    QString saveFilePath;
    QString saveFileName;

    void run();
signals:
    void updateProgress(int value);
};
