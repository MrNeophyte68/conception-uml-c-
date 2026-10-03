#include "UI/UIController.h"
#include "State/Commande.h"
#include "Miscellaneous/StockManager.h"
#include "ui/ConsoleColors.h"
#include "Command/AjouterGarnitureCommand.h"
#include "Command/CommandManager.h"

void UIController::afficherBienvenue() {
    std::cout << ConsoleColor::cyan << ConsoleColor::bold << "Bienvenue sur TonYogourt" << ConsoleColor::reset << std::endl;
}

void UIController::afficherHelp() {
    std::vector<std::pair<std::string, std::string>> helpList = {
        {"c nature|grec", "Ajouter un yogourt (max 2)"},
        {"sel 1|2", "Selectionner le yogourt actif"},
        {"f", "Ouvrir menu garnitures du yogourt actif"},
        {"u", "Annuler derniere garniture du yogourt actif"},
        {"r", "Refaire derniere garniture du yogourt actif"},
        {"p", "Preparer la commande"},
        {"t", "Terminer la commande"},
        {"mode prev|eclair|poly", "Changer le mode de paiement"},
        {"pay", "Finaliser paiement (etat Terminee requis)"},
        {"pay prev|eclair|poly", "Alias mode + payer"},
        {"total", "Afficher sous-total et total projete"},
        {"sub article", "S'abonner aux notifications d'un article"},
        {"unsub article", "Se desabonner d'un article"},
        {"subs", "Afficher abonnements actifs"},
        {"clear|cls", "Nettoyer l'ecran"},
        {"s", "Afficher les stocks"},
        {"h", "Aide"},
        {"q", "Quitter"}
    };

    std::cout << ConsoleColor::blue << ConsoleColor::bold << "Commandes:" << ConsoleColor::reset << std::endl;
    for (auto& cmd : helpList) {
        std::cout << std::left << std::setw(25) << cmd.first << "-> " << cmd.second << std::endl;
    }
}

void UIController::nettoyerEcran() {
    std::cout << std::string(200, '\n');
}

void UIController::afficherEtat(Commande* commande) {
    // affichage phase
    std::string stateName = commande->getState()->getName();
    if (stateName == "Initiale") {
        std::cout << "Phase: " << ConsoleColor::yellow << stateName << ConsoleColor::reset << std::endl;
    }
    else if (stateName == "En preparation") {
        std::cout << "Phase: " << ConsoleColor::blue << stateName << ConsoleColor::reset << std::endl;
    }
    else if (stateName == "Terminee") {
        std::cout << "Phase: " << ConsoleColor::cyan << stateName << ConsoleColor::reset << std::endl;
    }

    // affichage yogourt
    int selectedIndex = commande->getSelectedIndex();
    auto& yogourts = commande->getYogourtVector();
    if (selectedIndex == -1) {
        std::cout << "Yogourts: aucun" << std::endl;
    }
    else {
        for (int i = 0; i < yogourts.size(); i++) {
            if (i == selectedIndex) {
                std::cout << "Yogourt #" << (i + 1) << " (actif): ";
            }
            else {
                std::cout << "Yogourt #" << (i + 1) << ": ";
            }
            std::cout << yogourts[i]->getDescription() << " | Prix: " << std::fixed << std::setprecision(2) << yogourts[i]->getPrice() << " CAD" << std::endl;
        }

    }

    // affichage sous-total
    double sousTotal = 0.0;
    for (auto& y : yogourts) {
        sousTotal += y->getPrice();
    }
    std::cout << "Sous-total commande: " << std::fixed << std::setprecision(2) << sousTotal << " CAD" << std::endl;

    // affichage paiement
    std::cout << "Paiement: " << commande->getModePaiementDescription() << " | ";
    commande->afficherTotal();
    std::cout << " | ";
    commande->afficherPayable();
    std::cout << std::endl;
}

std::string UIController::lireInput() {
    std::string input;
    std::cout << ConsoleColor::magenta << "Commande: " << ConsoleColor::reset;
    std::getline(std::cin >> std::ws, input);
    return input;
}

void UIController::afficherMenuGarnitures(StockManager* stockManager, CommandManager* commandManager, Commande* commande) {
    if (commande->getSelectedIndex() == -1) {
        std::cout << ConsoleColor::reset << "Ajoute un yogourt d'abord." << ConsoleColor::reset << std::endl;
        return;
    }
    if (commande->getState()->getName() == "En preparation") {
        std::cout << ConsoleColor::reset << "Commande en preparation: ajout de garniture annulee." << ConsoleColor::reset << std::endl;
        return;
    }
    std::string choix;

    while (true) {
        std::cout << ConsoleColor::blue << ConsoleColor::bold << "Menu Garnitures" << ConsoleColor::reset << std::endl;
        std::cout << ConsoleColor::reset << "Yogourts actif: #" << ((commande->getSelectedIndex() == 0) ? "1" : "2") << ConsoleColor::reset << std::endl;
        std::vector<std::string> options = stockManager->afficherMenuGarnitures();
        std::cout << ConsoleColor::magenta << "Choix garniture: " << ConsoleColor::reset;
        if (!std::getline(std::cin >> std::ws, choix) || choix == "q") break;

        try {
            int n = std::stoi(choix) - 1;
            if (n >= 0 && n < options.size()) {
                if (stockManager->retirerStock(options[n])) {
                    commandManager->execute(std::make_unique<AjouterGarnitureCommand>(commande, options[n], stockManager));
                    std::cout << std::endl;
                }
            }
            else {
                std::cout << "Choix doit etre entre 1 et " << std::to_string(options.size()) << std::endl;
                std::cout << std::endl;
            }
        }
        catch (...) {
            std::cout << ConsoleColor::reset << "Choix invalide." << std::endl;
            std::cout << std::endl;
        }
    }
}

void UIController::afficherMessage(const std::string& message) {
    std::cout << ConsoleColor::reset << message << std::endl;
}