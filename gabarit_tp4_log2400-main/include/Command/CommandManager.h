//
// Created by akhan on 2026-04-04.
//

#pragma once
#include <memory>
#include <vector>
#include "Command.h"

class Command;

class CommandManager {
    private:
        std::vector<std::unique_ptr<Command>> history;
        int currentIndex = -1;

    public:
        void execute(std::unique_ptr<Command> cmd);
        void undo();
        void redo();
};
