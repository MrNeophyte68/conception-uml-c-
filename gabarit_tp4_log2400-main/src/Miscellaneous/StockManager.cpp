//
// Created by akhan on 2026-04-03.
//
#include "Miscellaneous/StockManager.h"

void StockManager::afficherStock() {
    std::cout << ConsoleColor::blue << ConsoleColor::bold << "Stocks:" << ConsoleColor::reset << std::endl;

    for (auto& stock : stockMap) {
        std::cout << std::left << std::setw(10) << stock.first + ": " << std::right << std::to_string(stock.second.stockQuantity) << std::endl;
    }
}

void StockManager::setStock(const std::string &stockName, int stockNumber, std::function<std::unique_ptr<Subscriber>()> stockType) {
    stockMap[stockName] = {stockNumber, std::move(stockType)};
    std::cout << ConsoleColor::blue << "[Stock] " << ConsoleColor::reset << stockName << " : 0 -> " << std::to_string(stockNumber) << ConsoleColor::reset << std::endl;
}

bool StockManager::retirerStock(const std::string &stockName) {

    auto it = stockMap.find(stockName);

    if (it != stockMap.end()) {
        if (it->second.stockQuantity > 0) {
            int beforeValue = it->second.stockQuantity;
            it->second.stockQuantity--;
            std::cout << ConsoleColor::blue << "[Stock] " << ConsoleColor::reset << stockName << " : " << std::to_string(beforeValue) << " -> " << std::to_string(it->second.stockQuantity) << ConsoleColor::reset << std::endl;
            if (it->second.stockQuantity == 0) notifyObservers(stockName, WARNING::Rupture);
            return true;
        } else {
            std::cout << "Stock insuffisant pour " << ((stockName != "nature" && stockName != "grec") ? "la garniture " : "le yogourt ") << "'" << stockName << "'." << std::endl;
            std::cout << std::endl;
            return false;
        }
    }
    std::cout << "Le stock " << "'" << stockName << "' n'existe pas." << std::endl;
    return false;
}

bool StockManager::ajouterStock(const std::string &stockName) {
    auto it = stockMap.find(stockName);

    if (it != stockMap.end()) {
        int beforeValue = it->second.stockQuantity;
        it->second.stockQuantity++;
        std::cout << ConsoleColor::blue << "[Stock] " << ConsoleColor::reset << stockName << " : " << std::to_string(beforeValue) << " -> " << std::to_string(it->second.stockQuantity) << ConsoleColor::reset << std::endl;
        if (beforeValue == 0) notifyObservers(stockName, WARNING::Retour);
        return true;
    }
    return false;
}

std::vector<std::string> StockManager::afficherMenuGarnitures() {
    int stockNumber = 0;
    std::vector<std::string> options;

    for (auto& stock : stockMap) {
        if (stock.first == "nature" || stock.first == "grec") continue;
        options.push_back(stock.first);
        std::cout << std::to_string(++stockNumber) << " -> ";
        std::cout << std::left << std::setw(10) << stock.first << "(" << std::to_string(stock.second.stockQuantity) << " en stock)" << std::endl;
    }
    std::cout << "q -> retour menu principal" << std::endl;
    return options;
}

void StockManager::addObserver(const std::string &stockName) {
    auto it = stockMap.find(stockName);
    if (it != stockMap.end()) {
        observers.push_back(it->second.stockType());
        std::cout << ConsoleColor::cyan << "[Abonnement] " << ConsoleColor::reset << "Notifications actives pour '" + stockName + "'." << std::endl;
        return;
    }
    std::cout << "Article introuvable." << std::endl;
}

void StockManager::removeObserver(const std::string &stockName) {
    auto it = stockMap.find(stockName);
    if (it != stockMap.end()) {
        observers.erase(std::remove_if(observers.begin(), observers.end(),
        [&stockName](const std::unique_ptr<Subscriber>& sub) {
            return sub->getName() == stockName;
        }), observers.end());
        std::cout << ConsoleColor::cyan << "[Abonnement] " << ConsoleColor::reset << "Desabonne de '" + stockName + "'." << std::endl;
        return;
    }
    std::cout << "Article introuvable." << std::endl;
}

void StockManager::notifyObservers(const std::string &stockName, WARNING type) {
    for (std::unique_ptr<Subscriber>& sub : observers) {
        sub->update(stockName, type);
    }
}

void StockManager::showObservers() {
    std::cout << ConsoleColor::blue << ConsoleColor::bold << "Abonnements actifs:" << ConsoleColor::reset << std::endl;
    for (auto& obs : observers) {
        std::cout << ConsoleColor::reset << "-" + obs->getName() << std::endl;
    }
}
