//
// Created by akhan on 2026-04-04.
//
#include "DecoratorAndPrototype/GarnitureFruits.h"

std::string Fruits::getDescription() const {
    return wrappedYogourt->getDescription() + " + fruits";
}

double Fruits::getPrice() const {
    return wrappedYogourt->getPrice() + 1.00;
}

std::unique_ptr<Yogourt> Fruits::clone() const {
    return std::make_unique<Fruits>(wrappedYogourt->clone());
}

void Fruits::update(const std::string& name, WARNING type) {
    if (name != "fruits") return;
    switch (type) {
        case WARNING::Rupture:
            std::cout << ConsoleColor::red << "[Notif Abonne] " << ConsoleColor::reset << "Rupture de stock pour 'fruits'." << ConsoleColor::reset << std::endl ;
            break;
        case WARNING::Retour:
            std::cout << ConsoleColor::cyan << "[Notif Abonne] " << ConsoleColor::reset << "'fruits' est de retour en stock." << ConsoleColor::reset << std::endl ;
            break;
    }
}