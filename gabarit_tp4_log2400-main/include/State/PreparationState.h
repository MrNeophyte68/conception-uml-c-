//
// Created by akhan on 2026-04-02.
//

#pragma once
#include "CommandeState.h"
#include "ui/ConsoleColors.h"
#include <memory>
#include <string>
#include <iostream>

class PreparationState : public CommandeState {
    public:
        PreparationState(Commande* c) : CommandeState(c) {}
        std::string getName() const override;
        bool ajouterYogourt(Commande *c, const std::string &type) override;
        void ajouterGarniture(Commande *c, const std::string &type) override;
        void afficherPayable() override;
        void payer(Commande* c) override;
};