//
// Created by akhan on 2026-04-02.
//

#include "Singleton/Application.h"

std::unique_ptr<Application> Application::instance = nullptr;

Application* Application::getInstance() {
    if (!instance) {
        instance.reset(new Application());
        instance->currentCommande = std::make_unique<Commande>();
        instance->currentStockManager = std::make_unique<StockManager>();
        instance->currentCommandManager = std::make_unique<CommandManager>();
        instance->ui = std::make_unique<UIController>();
    }
    return instance.get();
}

void Application::run() {
    std::string input;

    //execute only once before running
    //=======================================
    currentStockManager->setStock("nature", 3, []() {return std::make_unique<YogourtNature>();});
    currentStockManager->setStock("grec", 1, []() {return std::make_unique<YogourtGrec>();});
    currentStockManager->setStock("fruits", 5, []() {return std::make_unique<Fruits>();});
    currentStockManager->setStock("granola", 4, []() {return std::make_unique<Granola>();});
    currentStockManager->setStock("miel", 4, []() {return std::make_unique<Miel>();});
    currentStockManager->setStock("chocolat", 1, []() {return std::make_unique<Chocolat>();});
    ui->afficherBienvenue();
    ui->afficherHelp();
    //=======================================

    while (running) {
        ui->afficherEtat(currentCommande.get());
        std::string input = ui->lireInput();
        interpret(input);
        ui->afficherMessage("\n");
    }

}

void Application::interpret(const std::string& cmd) {
    auto tokens = splitString(cmd, ' ');
    if (tokens.empty()) return;
    const std::string& token = tokens[0];

    static std::unordered_map<std::string, std::function<void()>> simpleCommands = {
        {"q", [this]() {running = false;}},
        {"h", [this]() {ui->afficherHelp();}},
        {"clear", [this]() {ui->nettoyerEcran();}},
        {"cls", [this]() {ui->nettoyerEcran();}},
        {"total", [this]() {currentCommande->afficherSousTotal();}},
        {"subs", [this]() {currentStockManager->showObservers();}},
        {"f", [this]() {ui->afficherMenuGarnitures(currentStockManager.get(), currentCommandManager.get(), currentCommande.get()); }},
        {"pay", [this]() {
            currentCommande->payer();
            if (currentCommande->getState()->getName() == "Terminee" && currentCommande->getModePaiementDescription() != "Aucune") running = false;
        }},
        {"s", [this]() {currentStockManager->afficherStock();}},
        {"u", [this]() {
            if (currentCommande->getState()->getName() == "En preparation") {
                ui->afficherMessage("Commande en preparation: annulation verrouillee.");
                return;
            }
            currentCommandManager->undo();
        }},
        {"r", [this]() {
            if (currentCommande->getState()->getName() == "En preparation") {
                ui->afficherMessage("Commande en preparation: retour verrouillee.");
                return;
            }
            currentCommandManager->redo();
        }},
        {"p", [this]() {
            if (currentCommande->getYogourtVectorSize() == 0) {
                ui->afficherMessage("Impossible de preparer sans yogourt.");
                return;
            }
            if (currentCommande->getState()->getName() == "En preparation") {
                ui->afficherMessage("Commande deja en preparation.");
                return;
            }
            if (currentCommande->getState()->getName() == "Terminee") {
                ui->afficherMessage("Commande terminee: impossible de preparer.");
                return;
            }
            currentCommande->preparer();
        }},
        {"t", [this]() {
            if (currentCommande->getState()->getName() == "Initiale") {
                ui->afficherMessage("La commande doit etre preparee avant d'etre terminee.");
                return;
            }
            if (currentCommande->getState()->getName() == "Terminee") {
                ui->afficherMessage("Commande terminee: impossible de terminer encore.");
                return;
            }
            currentCommande->terminer();
        }},
    };

    if (tokens.size() == 1) {
        if (auto it = simpleCommands.find(token); it != simpleCommands.end()) {
            it->second();
            return;
        }
    }
    else {
        //pour les commands qui ont plus que un parametre
        if (tokens[0] == "c") {
            if (tokens.size() == 2) {
                if (currentCommande->ajouterYogourt(tokens[1])) {
                    if (currentStockManager->retirerStock(tokens[1])) return;
                }
            } else {
                std::cout << "Erreur: La syntaxe est 'c <type_yogourt>'" << std::endl;
            }
            return;
        }

        else if (tokens[0] == "sel") {
            if (currentCommande->getState()->getName() == "En preparation") {
                std::cout << ConsoleColor::reset << "Commande en preparation: selection verrouillee." << std::endl;
                return;
            }
            if (tokens.size() == 2) {
                currentCommande->selectYogourt(tokens[1]);
            } else {
                std::cout << "Erreur: La syntaxe est 'sel 1|2'" << std::endl;
            }
            return;
        }

        else if (tokens[0] == "mode") {
            if (tokens.size() == 2) {
                currentCommande->changerMode(tokens[1]);
            } else {
                std::cout << "Erreur: La syntaxe est 'mode prev|eclair|poly'" << std::endl;
            }
            return;
        }

        else if (tokens[0] == "pay") {
            if (tokens.size() == 2) {
                currentCommande->changerModeEtPayer(tokens[1]);
                if (currentCommande->getState()->getName() == "Terminee" && currentCommande->getModePaiementDescription() != "Aucune") running = false;
            } else {
                std::cout << "Erreur: La syntaxe est 'pay prev|eclair|poly'" << std::endl;
            }
            return;
        }

        else if (tokens[0] == "sub") {
            if (tokens.size() == 2) {
                currentStockManager->addObserver(tokens[1]);
            } else {
                std::cout << "Erreur: La syntaxe est 'sub article'" << std::endl;
            }
            return;
        }

        else if (tokens[0] == "unsub") {
            if (tokens.size() == 2) {
                currentStockManager->removeObserver(tokens[1]);
            } else {
                std::cout << "Erreur: La syntaxe est 'unsub article'" << std::endl;
            }
            return;
        }
    }
    std::cout << "Commande introuvable: " << tokens[0] << std::endl;
}