//
// Created by akhan on 2026-04-02.
//

#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Miscellaneous/StockManager.h"
#include <unordered_map>
#include <functional>
#include <State/PreparationState.h>
#include "Command/CommandManager.h"
#include "State/Commande.h"
#include "State/CommandeState.h"
#include "Command/AjouterGarnitureCommand.h"
#include "DecoratorAndPrototype/YogourtNature.h"
#include "DecoratorAndPrototype/YogourtGrec.h"
#include "DecoratorAndPrototype/GarnitureChocolat.h"
#include "DecoratorAndPrototype/GarnitureFruits.h"
#include "DecoratorAndPrototype/GarnitureMiel.h"
#include "DecoratorAndPrototype/GarnitureGranola.h"
#include "ui/UIController.h"

class Commande;
class StockManager;
class Chocolat;
class YogourtGrec;
class YogourtNature;

class Application {
private:
    bool running = true;
    static std::unique_ptr<Application> instance;
    std::unique_ptr<Commande> currentCommande;
    std::unique_ptr<StockManager> currentStockManager;
    Application() = default;
    void interpret(const std::string& cmd);
    std::unique_ptr<CommandManager> currentCommandManager;
    std::unique_ptr<UIController> ui;

    //prevent copy
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

public:
    virtual ~Application() = default;
    static Application* getInstance();
    void run();
};

inline std::vector<std::string> splitString(const std::string& input, char delimiter = ' ') {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    while (std::getline(iss, token, delimiter)) {
        if (!token.empty()) tokens.push_back(token);
    }
    return tokens;
}
