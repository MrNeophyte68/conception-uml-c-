//
// Created by akhan on 2026-04-02.
//
#include "State/Commande.h"
#include "State/InitialState.h"

Commande::Commande() {
    currentState = std::make_unique<InitialState>(this);
    modePaiement = std::make_unique<ModePaiement>();
}

void Commande::setState(std::unique_ptr<CommandeState> state) {
    currentState = std::move(state);
    if (currentState && currentState->getName() == "En preparation") {
        std::cout << ConsoleColor::reset << "Preparation en cours..." << ConsoleColor::reset << std::endl;
    }
}

CommandeState* Commande::getState() const {
    return currentState.get();
}

int Commande::getSelectedIndex() const {
    return selectedIndex;
}

int Commande::getYogourtVectorSize() const {
    return yogourts.size();
}

std::vector<std::unique_ptr<Yogourt>>& Commande::getYogourtVector() {
    return yogourts;
}

bool Commande::ajouterYogourt(const std::string &type) {
    return currentState->ajouterYogourt(this, type);
}

void Commande::afficherSousTotal() {
    if (selectedIndex == -1 && getModePaiementDescription() == "Aucune") {
        std::cout << ConsoleColor::blue << "Sous-total: 0.00 CAD" << ConsoleColor::reset << std::endl;
        return;
    }
    if (selectedIndex == -1 && getModePaiementDescription() != "Aucune") {
        if (getModePaiementDescription() == "Vente eclair (+1.50)") {
            std::cout << ConsoleColor::blue << "Sous-total: 0.00 CAD" << ConsoleColor::reset << std::endl;
            std::cout << ConsoleColor::blue << "Total avec " + getModePaiementDescription() + ": ";
            std::cout << "1.50 CAD" << ConsoleColor::reset << std::endl;
        }
        std::cout << ConsoleColor::blue << "Sous-total: 0.00 CAD" << ConsoleColor::reset << std::endl;
        std::cout << ConsoleColor::blue << "Total avec " + getModePaiementDescription() + ": ";
        std::cout << "0.00 CAD" << ConsoleColor::reset << std::endl;
        return;
    }
    std::ostringstream o;
    o << std::fixed << std::setprecision(2) << yogourts[selectedIndex]->getPrice();
    std::cout << ConsoleColor::blue << "Sous-total: " << o.str() << " CAD" << ConsoleColor::reset << std::endl;
    std::cout << ConsoleColor::blue << "Total avec " + getModePaiementDescription() + ": ";
    double prix = modePaiement->calculerPrix(yogourts[selectedIndex]->getPrice());
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << prix;
    std::cout << oss.str() << " CAD" << ConsoleColor::reset << std::endl;
}

void Commande::selectYogourt(const std::string &index) {
    if (index != "1" && index != "2") {
        std::cout << ConsoleColor::reset << "Doit etre 1 ou 2." << ConsoleColor::reset << std::endl;
        return;
    }
    if (yogourts.size() == 1 && index == "2") {
        std::cout << ConsoleColor::reset << "Le deuxieme yogourt n'existe pas encore." << ConsoleColor::reset << std::endl;
        return;
    }
    if (yogourts.empty()) {
        std::cout << ConsoleColor::reset << "Il n'y a pas de yogourts." << ConsoleColor::reset << std::endl;
        return;
    }
    selectedIndex = std::stoi(index) - 1;
    std::cout << ConsoleColor::reset << yogourts[selectedIndex]->getDescription() << " selectionne." << ConsoleColor::reset << std::endl;
}

std::string Commande::displayCurrentYogourtDescription() {
    if (selectedIndex == -1) {
        return "aucun";
    }
    return getYogourtVector()[selectedIndex]->getDescription();
}

std::string Commande::displayCurrentYogourtPrix() {
    if (selectedIndex == -1) {
        return "0.00";
    }
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << getYogourtVector()[selectedIndex]->getPrice();
    return oss.str();
}

void Commande::ajouterGarniture(const std::string &type) {
    currentState->ajouterGarniture(this, type);
}

void Commande::preparer() {
    setState(std::make_unique<PreparationState>(this));
}

void Commande::terminer() {
    setState(std::make_unique<TerminerState>(this));
}

void Commande::afficherPayable() {
    currentState->afficherPayable();
}

void Commande::payer() {
    currentState->payer(this);
}

void Commande::changerModeEtPayer(const std::string &mode) {
    changerMode(mode);
    payer();
}

void Commande::changerMode(const std::string& mode) {
    if (mode == "prev") {
        modePaiement = std::move(std::make_unique<ModePrev>());
        std::cout << ConsoleColor::cyan << "Mode de paiement actif: " + modePaiement->getDescription() << ConsoleColor::reset << std::endl;
        return;
    }
    else if (mode == "eclair") {
        modePaiement = std::move(std::make_unique<ModeEclair>());
        std::cout << ConsoleColor::cyan << "Mode de paiement actif: " + modePaiement->getDescription() << ConsoleColor::reset << std::endl;
        return;
    }
    else if (mode == "poly") {
        modePaiement = std::move(std::make_unique<ModePoly>());
        std::cout << ConsoleColor::cyan << "Mode de paiement actif: " + modePaiement->getDescription() << ConsoleColor::reset << std::endl;
        return;
    }
    else {
        std::cout << "Ce mode n'existe pas." << ConsoleColor::reset << std::endl;
    }
}

std::string Commande::getModePaiementDescription() const {
    return modePaiement->getDescription();
}

void Commande::afficherTotal() {
    if (selectedIndex == -1 && getModePaiementDescription() == "Aucune") {
        std::cout << ConsoleColor::yellow << "choisir un mode de paiement" << ConsoleColor::reset;
        return;
    }
    if (selectedIndex == -1 && getModePaiementDescription() != "Aucune") {
        std::cout << "Total projete: 0.00 CAD" << ConsoleColor::reset;
        return;
    }
    double prix = modePaiement->calculerPrix(yogourts[selectedIndex]->getPrice());
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << prix;
    std::cout << "Total projete: " << oss.str() << " CAD" << ConsoleColor::reset;
}