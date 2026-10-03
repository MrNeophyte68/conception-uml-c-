//
// Created by akhan on 2026-04-04.
//
#include "DecoratorAndPrototype/GarnitureChocolat.h"

std::string Chocolat::getDescription() const {
    return wrappedYogourt->getDescription() + " + chocolat";
}

double Chocolat::getPrice() const {
    return wrappedYogourt->getPrice() + 0.90;
}

std::unique_ptr<Yogourt> Chocolat::clone() const {
    return std::make_unique<Chocolat>(wrappedYogourt->clone());
}

void Chocolat::update(const std::string& name, WARNING type) {
    if (name != "chocolat") return;
    switch (type) {
        case WARNING::Rupture:
            std::cout << ConsoleColor::red << "[Notif Abonne] " << ConsoleColor::reset << "Rupture de stock pour 'chocolat'." << ConsoleColor::reset << std::endl ;
            break;
        case WARNING::Retour:
            std::cout << ConsoleColor::cyan << "[Notif Abonne] " << ConsoleColor::reset << "'chocolat' est de retour en stock." << ConsoleColor::reset << std::endl ;
            break;
    }
}