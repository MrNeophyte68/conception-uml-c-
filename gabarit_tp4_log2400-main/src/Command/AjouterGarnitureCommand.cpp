//
// Created by akhan on 2026-04-04.
//

#include "Command/AjouterGarnitureCommand.h"

AjouterGarnitureCommand::AjouterGarnitureCommand(Commande* c, const std::string& t, StockManager* s) : commande(c), type(t), stockManager(s) {}

void AjouterGarnitureCommand::execute() {
    std::vector<std::unique_ptr<Yogourt>>& yogourts = commande->getYogourtVector();
    index = commande->getSelectedIndex();

    if (index < 0 || index >= yogourts.size()) return;

    //prototype logic
    backup = yogourts[index]->clone();

    commande->ajouterGarniture(type);
    std::cout << ConsoleColor::reset << "Garniture '" + type + "' ajoutee." << ConsoleColor::reset << std::endl;
}

void AjouterGarnitureCommand::undo() {
    std::vector<std::unique_ptr<Yogourt>>& yogourts = commande->getYogourtVector();
    if (index < 0 || index >= yogourts.size()) return;
    if (stockManager->ajouterStock(type)) {
        yogourts[index] = backup->clone();
        std::cout << "Derniere garniture annulee." << std::endl;
        std::cout << std::endl;
    }
}

void AjouterGarnitureCommand::redo() {
    std::vector<std::unique_ptr<Yogourt>>& yogourts = commande->getYogourtVector();
    if (index < 0 || index >= yogourts.size()) return;
    if (stockManager->retirerStock(type)) {
        commande->ajouterGarniture(type);
    }
}