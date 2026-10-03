//
// Created by akhan on 2026-04-02.
//
#pragma once
#include "CommandeState.h"
#include <string>
#include <iostream>
#include "Factory/YogourtFactory.h"
#include "ui/ConsoleColors.h"
#include "Commande.h"
#include "DecoratorAndPrototype/GarnitureChocolat.h"
#include "DecoratorAndPrototype/GarnitureGranola.h"
#include "DecoratorAndPrototype/GarnitureMiel.h"
#include "DecoratorAndPrototype/GarnitureFruits.h"
#include <memory>

class Commande;

class InitialState : public CommandeState {
    public:
        InitialState(Commande* c) : CommandeState(c) {}
        std::string getName() const override;
        bool ajouterYogourt(Commande* c, const std::string& type) override;
        void ajouterGarniture(Commande* c, const std::string& type) override;
        void afficherPayable() override;
        void payer(Commande* c) override;
};