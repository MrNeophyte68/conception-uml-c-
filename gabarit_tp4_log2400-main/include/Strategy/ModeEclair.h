//
// Created by akhan on 2026-04-02.
//

#pragma once
#include "ModePaiement.h"

class ModeEclair : public ModePaiement {
public:
    double calculerPrix(double montant) override;
    std::string getDescription() override;
};
