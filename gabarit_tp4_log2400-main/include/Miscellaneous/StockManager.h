//
// Created by akhan on 2026-04-03.
//

#pragma once
#include <functional>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <iostream>
#include <memory>
#include <algorithm>
#include "ui/ConsoleColors.h"
#include "Observer/Subscriber.h"
#include "Miscellaneous/WARNING.h"

class Subscriber;

class Commande;

struct stockInfo {
    int stockQuantity;
    std::function<std::unique_ptr<Subscriber>()> stockType;
};

class StockManager {
private:
    std::map<std::string, stockInfo> stockMap;
    std::vector<std::unique_ptr<Subscriber>> observers;
public:
    StockManager() = default;
    ~StockManager() = default;

    std::vector<std::string> afficherMenuGarnitures();
    void afficherStock();
    bool retirerStock(const std::string& stockName);
    bool ajouterStock(const std::string& stockName);
    void setStock(const std::string& stockName, int stockNumber, std::function<std::unique_ptr<Subscriber>()>); //montre sur terminal

    //observateur
    void addObserver(const std::string& stockName);
    void removeObserver(const std::string& stockName);
    void notifyObservers(const std::string &stockName, WARNING type);
    void showObservers();
};
