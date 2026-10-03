//
// Created by akhan on 2026-04-02.
//

#pragma once
#include <memory>
#include <array>
//#include "State/InitialState.h"
#include <vector>
#include "DecoratorAndPrototype/Yogourt.h"
#include "ui/ConsoleColors.h"
#include <ostream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "Strategy/ModePaiement.h"
#include "State/PreparationState.h"
#include "State/TerminerState.h"
#include "Strategy/ModeEclair.h"
#include "Strategy/ModePoly.h"
#include "Strategy/ModePrev.h"

class ModePaiement;
class CommandeState;

class Commande {
private:
    int selectedIndex = -1;
    //factory - vector pour yogourt
    std::vector<std::unique_ptr<Yogourt>> yogourts;
    //strategy
    std::unique_ptr<ModePaiement> modePaiement;
    //state
    std::unique_ptr<CommandeState> currentState;
public:
    Commande();
    ~Commande() = default;

    //state methods
    void setState(std::unique_ptr<CommandeState> state);
    CommandeState* getState() const;
    void preparer();
    void terminer();

    //basic methods
    int getSelectedIndex() const;
    int getYogourtVectorSize() const;
    std::vector<std::unique_ptr<Yogourt>>& getYogourtVector();
    bool ajouterYogourt(const std::string& type);
    void selectYogourt(const std::string& index);
    std::string displayCurrentYogourtDescription();
    std::string displayCurrentYogourtPrix();

    //decorator
    void ajouterGarniture(const std::string& type);

    //command
    void undo();
    void redo();

    //strategie
    void payer();
    void changerModeEtPayer(const std::string& mode);
    void changerMode(const std::string& mode);
    void afficherTotal();
    std::string getModePaiementDescription() const;
    void afficherPayable();
    void afficherSousTotal();
};