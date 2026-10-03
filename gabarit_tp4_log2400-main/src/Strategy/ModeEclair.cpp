//
// Created by akhan on 2026-04-02.
//
#include "Strategy/ModeEclair.h"

std::string ModeEclair::getDescription() {
    return "Vente eclair (+1.50)";
}

double ModeEclair::calculerPrix(double montant) {
    return montant+1.50;
}