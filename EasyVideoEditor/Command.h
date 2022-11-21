#pragma once

#include <opencv2/opencv.hpp>

class Command
{
public:
    // An enumeration of the type of command.
    enum CommandType {
        COLOR_EMPHASIS, CHANGE_BRIGHTNESS, CHANGE_CONTRAST, FILTER_EFFECT, CHROMAKEY, TRANSITION
        , ADD_IMAGE, ADD_VIDEO, CUT_VIDEO, RESIZE, CHANGE_PLAY_SPEED, ADD_SUBTITLE
    };
protected:
    // Command type.
    CommandType commandType;
public:
    // Default constructor.
    Command();

    // Default destructor.
    ~Command();

    // A pure virtual function overloaded with an operator that must be implemented in relation to a command in a class that inherits Command class.
    virtual void operator()() = 0;

    // A pure virtual function overloaded with an operator that must be implemented in relation to a command in a class that inherits Command class.
    virtual void operator()(cv::Mat* mat) = 0;

    // Command type setter.
    void setCommand(CommandType commandType);
    // Command type getter.
    CommandType getCommand();
};