#pragma once

#include <iostream>
#include <list>
#include <string>
#include "Command.h"

class Frame
{
private:
    std::list<Command*> commandList;
    int sourceId;
    int sourceFrameIndex;
public:
    Frame();
    ~Frame();

    void setFrameInfo(int sourceId, int sourceFrameIndex);
    Command* getCommand(int index);

    void addCommand(Command* command);
    void removeAllCommand();
    void removeLastCommand();
    void removeCommand(int index);
    void removeCommand(Command* command);
public:
    void setSourceId(int sourceId);
    void setSourceFrameIndex(int sourceFrameIndex);
    void setCommandList(std::list<Command*> commandList);
    int getSourceId();
    int getSourceFrameIndex();
    std::list<Command*>* getCommandList();
};

