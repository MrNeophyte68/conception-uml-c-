//
// Created by akhan on 2026-04-02.
//

#include "State/PreparationState.h"

std::string PreparationState::getName() const {
    return "En preparation";
}

bool PreparationState::ajouterYogourt(Commande* c, const std::string& type) {
    std::cout << ConsoleColor::reset << "Commande en preparation: creation de yogourt annulee." << ConsoleColor::reset << std::endl;
    return false;
}

void PreparationState::ajouterGarniture(Commande *c, const std::string &type) {
    std::cout << ConsoleColor::reset << "Commande en preparation: ajout de garniture annulee." << ConsoleColor::reset << std::endl;
}

void PreparationState::afficherPayable() {
    std::cout << ConsoleColor::red << "non payable" << ConsoleColor::reset;
}

void PreparationState::payer(Commande *c) {
    std::cout << ConsoleColor::red << "Paiement refuse: etat Terminee requis (etat actuel: En preparation)." << ConsoleColor::reset << std::endl;
}