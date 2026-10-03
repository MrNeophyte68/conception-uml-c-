//
// Created by akhan on 2026-04-04.
//
#include "DecoratorAndPrototype/GarnitureGranola.h"

std::string Granola::getDescription() const {
    return wrappedYogourt->getDescription() + " + granola";
}

double Granola::getPrice() const {
    return wrappedYogourt->getPrice() + 0.80;
}

std::unique_ptr<Yogourt> Granola::clone() const {
    return std::make_unique<Granola>(wrappedYogourt->clone());
}

void Granola::update(const std::string& name, WARNING type) {
    if (name != "granola") return;
    switch (type) {
        case WARNING::Rupture:
            std::cout << ConsoleColor::red << "[Notif Abonne] " << ConsoleColor::reset << "Rupture de stock pour 'granola'." << ConsoleColor::reset << std::endl ;
            break;
        case WARNING::Retour:
            std::cout << ConsoleColor::cyan << "[Notif Abonne] " << ConsoleColor::reset << "'granola' est de retour en stock." << ConsoleColor::reset << std::endl ;
            break;
    }
}