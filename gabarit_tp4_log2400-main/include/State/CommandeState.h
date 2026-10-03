//
// Created by akhan on 2026-04-02.
//

#pragma once
#include <string>

class Commande;

class CommandeState {
    protected:
        Commande* commande;

    public:
        virtual ~CommandeState() = default;
        CommandeState(Commande* c) : commande(c) {}
        virtual std::string getName() const = 0;
        virtual bool ajouterYogourt(Commande* c, const std::string& type) = 0;
        virtual void ajouterGarniture(Commande* c, const std::string& type) = 0;
        virtual void payer(Commande* c) = 0;
        virtual void afficherPayable() = 0;
};
