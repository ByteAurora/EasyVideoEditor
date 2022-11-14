#include "Command.h"

Command::Command() {

}

Command::~Command() {

}

void Command::setCommand(Command::CommandType commandType) {
    this->commandType = commandType;
}

Command::CommandType Command::getCommand() {
    return commandType;
}