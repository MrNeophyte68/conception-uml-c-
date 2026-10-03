//
// Created by akhan on 2026-04-02.
//
#pragma once
#include <iostream>
#include <memory>
#include <string>

class ModePaiement {
public:
    virtual ~ModePaiement() = default;
    ModePaiement() = default;
    virtual double calculerPrix(double montant) {return 0.00;} ;
    virtual std::string getDescription() {return "Aucune";};
};