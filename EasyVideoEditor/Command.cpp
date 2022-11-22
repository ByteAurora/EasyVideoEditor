#include "Command.h"

std::vector<Command*> Command::commandList;

Command::Command() {
}

Command::Command(bool addToList) {
    if (addToList) commandList.push_back(this);
}

Command::~Command() {

}

void Command::setCommand(Command::CommandType commandType) {
    this->commandType = commandType;
}

Command::CommandType Command::getCommand() {
    return commandType;
}