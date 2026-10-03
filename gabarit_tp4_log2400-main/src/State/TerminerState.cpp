//
// Created by akhan on 2026-04-02.
//
#include "State/TerminerState.h"

std::string TerminerState::getName() const {
    return "Terminee";
}

bool TerminerState::ajouterYogourt(Commande* c, const std::string& type) {
    std::cout << ConsoleColor::reset << "Commande terminee: creation de yogourt annulee." << ConsoleColor::reset << std::endl;
    return false;
}

void TerminerState::ajouterGarniture(Commande *c, const std::string &type) {
    std::cout << ConsoleColor::reset << "Commande terminee: ajout de garniture annulee." << ConsoleColor::reset << std::endl;
}

void TerminerState::afficherPayable() {
    std::cout << ConsoleColor::cyan << "payable" << ConsoleColor::reset;
}

void TerminerState::payer(Commande *c) {
    if (c->getModePaiementDescription() == "Aucune") {
        std::cout << ConsoleColor::red << "Paiement refuse: choisissez d'abord un mode (mode prev|eclair|poly)." << ConsoleColor::reset << std::endl;
        return;
    }
    std::cout << ConsoleColor::cyan << "Paiement accepte (" + c->getModePaiementDescription() + ") | Montant: ";
    c->afficherTotal();
    std::cout << std::endl;
    std::cout << ConsoleColor::cyan << ConsoleColor::bold << "Merci pour votre achat. A bientot!" << ConsoleColor::reset << std::endl;
}