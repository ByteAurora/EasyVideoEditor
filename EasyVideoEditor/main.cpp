#include "EasyVideoEditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EasyVideoEditor w;
    w.show();
    return a.exec();
}
