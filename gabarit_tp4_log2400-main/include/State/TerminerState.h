//
// Created by akhan on 2026-04-02.
//

#pragma once
#include "CommandeState.h"
#include <iostream>
#include "ui/ConsoleColors.h"
#include <memory>
#include <string>
#include "State/Commande.h"

class TerminerState : public CommandeState {
public:
    TerminerState(Commande* commande) : CommandeState(commande) {}
    void payer(Commande* c) override;
    std::string getName() const override;
    bool ajouterYogourt(Commande *c, const std::string &type);
    void ajouterGarniture(Commande *c, const std::string &type);
    void afficherPayable() override;
};