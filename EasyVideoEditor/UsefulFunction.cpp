#include "UsefulFunction.h"

int UsefulFunction::getMillisecondsFromString(QString timeString) {
    int hours = timeString.mid(0, 2).toInt();
    int minutes = timeString.mid(3, 2).toInt();
    int seconds = timeString.mid(6, 2).toInt();
    int milliseconds = timeString.mid(9, 3).toInt();

    return hours * minutes * seconds * 1000 + milliseconds;
}