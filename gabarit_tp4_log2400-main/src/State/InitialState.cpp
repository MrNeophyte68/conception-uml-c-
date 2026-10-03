//
// Created by akhan on 2026-04-02.
//

#include "State/InitialState.h"

std::string InitialState::getName() const {
    return "Initiale";
}

bool InitialState::ajouterYogourt(Commande* c, const std::string& type) {
    std::unique_ptr<Yogourt> y = YogourtFactory::createYogourt(type);
    if (!y) {
        std::cout << ConsoleColor::reset << "Type de yogourt invalide." << ConsoleColor::reset << std::endl;
        return false;
    }

    if (c->getYogourtVectorSize() >= 2) {
        std::cout << ConsoleColor::reset << "Seulement 2 yogourts maximum par commande." << ConsoleColor::reset << std::endl;
        return false;
    }

    c->getYogourtVector().push_back(std::move(y));
    c->selectYogourt(std::to_string(c->getYogourtVectorSize()));
    return true;
}

void InitialState::afficherPayable() {
    std::cout << ConsoleColor::red << "non payable" << ConsoleColor::reset;
}

void InitialState::payer(Commande *c) {
    std::cout << ConsoleColor::red << "Paiement refuse: etat Terminee requis (etat actuel: Initiale)." << ConsoleColor::reset << std::endl;
}

void InitialState::ajouterGarniture(Commande *c, const std::string &type) {
    auto& yogourts = c->getYogourtVector();
    int index = c->getSelectedIndex();
    std::unique_ptr<Yogourt> ancientYogourt = std::move(yogourts[index]);

    if (type == "chocolat") {
        yogourts[index] = std::make_unique<Chocolat>(std::move(ancientYogourt));
    }
    else if (type == "fruits") {
        yogourts[index] = std::make_unique<Fruits>(std::move(ancientYogourt));
    }
    else if (type == "granola") {
        yogourts[index] = std::make_unique<Granola>(std::move(ancientYogourt));
    }
    else if (type == "miel") {
        yogourts[index] = std::make_unique<Miel>(std::move(ancientYogourt));
    }
}
