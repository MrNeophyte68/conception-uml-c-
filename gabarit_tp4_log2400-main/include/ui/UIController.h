#pragma once
#include "Command/Command.h"
#include "Miscellaneous/StockManager.h"
#include "Command/CommandManager.h"

class UIController {

public:
	void afficherBienvenue();
	void afficherHelp();
	void afficherEtat(Commande* commande);
	void afficherMenuGarnitures(StockManager* stockManager, CommandManager* commandManager, Commande* commande);
	void nettoyerEcran();
	void afficherMessage(const std::string& message);
	std::string lireInput();
};