//
// Created by akhan on 2026-04-02.
//

#include "DecoratorAndPrototype/YogourtNature.h"

double YogourtNature::getPrice() const {
    return 2.00;
}

std::string YogourtNature::getDescription() const {
    return "Yogourt nature";
}

std::unique_ptr<Yogourt> YogourtNature::clone() const {
    return std::make_unique<YogourtNature>(*this);
}

void YogourtNature::update(const std::string& name, WARNING type) {
    if (name != "nature") return;
    switch (type) {
        case WARNING::Rupture:
            std::cout << ConsoleColor::red << "[Notif Abonne] " << ConsoleColor::reset << "Rupture de stock pour 'nature'." << ConsoleColor::reset << std::endl ;
            break;
        case WARNING::Retour:
            std::cout << ConsoleColor::cyan << "[Notif Abonne] " << ConsoleColor::reset << "'nature' est de retour en stock." << ConsoleColor::reset << std::endl ;
            break;
    }
}