//
// Created by akhan on 2026-04-04.
//
#include "DecoratorAndPrototype/GarnitureMiel.h"

std::string Miel::getDescription() const {
    return wrappedYogourt->getDescription() + " + miel";
}

double Miel::getPrice() const {
    return wrappedYogourt->getPrice() + 0.60;
}

std::unique_ptr<Yogourt> Miel::clone() const {
    return std::make_unique<Miel>(wrappedYogourt->clone());
}

void Miel::update(const std::string& name, WARNING type) {
    if (name != "miel") return;
    switch (type) {
        case WARNING::Rupture:
            std::cout << ConsoleColor::red << "[Notif Abonne] " << ConsoleColor::reset << "Rupture de stock pour 'miel'." << ConsoleColor::reset << std::endl ;
            break;
        case WARNING::Retour:
            std::cout << ConsoleColor::cyan << "[Notif Abonne] " << ConsoleColor::reset << "'miel' est de retour en stock." << ConsoleColor::reset << std::endl ;
            break;
    }
}