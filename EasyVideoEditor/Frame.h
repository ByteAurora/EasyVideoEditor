#pragma once

#include <iostream>
#include <list>
#include <string>
#include "Command.h"
#include "EveProject.h"

class EveProject;

/*
* @version  v1.0.0
* @author   Sohn Young Jin
* @since    v1.0.0
*
* The Frame class is used for efficient memory management.
* Instead of data about the actual frame, it has information about the original video to which the frame belongs and
* the index of the frame in the video. In addition, all commands(tasks) applied to the frame are saved in list format.
*/
class Frame
{
private:
    // List of all commands applied to the frame.
    std::list<Command*> commandList;

    // Index of the video to which the frame belongs among the videos in EveProject.videoList.
    int sourceId;

    // The index of the frame in the image containing the frame.
    int sourceFrameIndex;
public:
    // Default constructor.
    Frame();

    // Custom constructor.
    Frame(int sourceId, int sourceFrameIndex);

    // Default destructor.
    ~Frame();

    // Deep copy.
    void copyTo(Frame* frame);

    // Set frame informations.
    void setFrameInfo(int sourceId, int sourceFrameIndex);

    // Get command corresponding to the index.
    Command* getCommand(int index);

    // Add command into command list.
    void addCommand(Command* command);

    // Remove all command in command list.
    void removeAllCommand();

    // Remove last added command in command list.
    void removeLastCommand();

    // Remove command corresponding to the index.
    void removeCommand(int index);

    // Remove command which same as parameter.
    void removeCommand(Command* command);

    // Get real frame data.
    Frame* getRealFrameData(int beforeSourceId, int beforeSourceFrameIndex, cv::Mat* mat, bool moveEvent);

    // Get command applied frame data.
    Frame* getCommandAppliedFrameData(int beforeSourceId, int beforeSourceFrameIndex, cv::Mat* mat, bool moveEvent);
public:
    // Source ID setter.
    void setSourceId(int sourceId);
    // Source ID getter.
    int getSourceId();

    // Source frame index setter.
    void setSourceFrameIndex(int sourceFrameIndex);
    // Source frame index getter.
    int getSourceFrameIndex();

    // Command list setter.
    void setCommandList(std::list<Command*> commandList);
    // Command list getter.
    std::list<Command*>* getCommandList();
};