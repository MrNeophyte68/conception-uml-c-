//
// Created by akhan on 2026-04-04.
//

#pragma once
#include "Command.h"
#include "Miscellaneous/StockManager.h"
#include "State/Commande.h"

class AjouterGarnitureCommand : public Command {
    private:
        Commande* commande;
        std::string type;
        int index = -1;
        std::unique_ptr<Yogourt> backup;
        StockManager* stockManager;

    public:
        AjouterGarnitureCommand(Commande* c, const std::string& t, StockManager* s);
        void execute() override;
        void undo() override;
        void redo() override;
};
