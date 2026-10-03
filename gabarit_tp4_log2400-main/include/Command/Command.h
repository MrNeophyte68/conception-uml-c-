//
// Created by akhan on 2026-04-04.
//

#pragma once

class Command {
    public:
        virtual ~Command() = default;
        virtual void execute() = 0;
        virtual void undo() = 0;
        virtual void redo() = 0;
};