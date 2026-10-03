//
// Created by akhan on 2026-04-04.
//
#include "Command/CommandManager.h"

#include <iostream>
#include <ostream>

void CommandManager::execute(std::unique_ptr<Command> cmd) {
    //efface le history pour creer un nouveau timeline
    if (currentIndex + 1 < history.size()) {
        history.erase(history.begin() + currentIndex + 1, history.end());
    }

    cmd->execute();
    history.push_back(std::move(cmd));
    currentIndex++;
}

void CommandManager::undo() {
    if (currentIndex >= 0) {
        history[currentIndex]->undo();
        currentIndex--;
    }
}

void CommandManager::redo() {
    if (currentIndex + 1 < history.size()) {
        currentIndex++;
        history[currentIndex]->redo();
        std::cout << "Garniture retablie." << std::endl;
        std::cout << std::endl;
    }
}