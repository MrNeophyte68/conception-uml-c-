//
// Created by akhan on 2026-04-02.
//

#include "DecoratorAndPrototype/YogourtGrec.h"

double YogourtGrec::getPrice() const {
    return 2.50;
}

std::string YogourtGrec::getDescription() const {
    return "Yogourt grec";
}

std::unique_ptr<Yogourt> YogourtGrec::clone() const {
    return std::make_unique<YogourtGrec>(*this);
}

void YogourtGrec::update(const std::string& name, WARNING type) {
    if (name != "grec") return;
    switch (type) {
        case WARNING::Rupture:
            std::cout << ConsoleColor::red << "[Notif Abonne] " << ConsoleColor::reset << "Rupture de stock pour 'grec'." << ConsoleColor::reset << std::endl ;
            break;
        case WARNING::Retour:
            std::cout << ConsoleColor::cyan << "[Notif Abonne] " << ConsoleColor::reset << "'grec' est de retour en stock." << ConsoleColor::reset << std::endl ;
            break;
    }
}