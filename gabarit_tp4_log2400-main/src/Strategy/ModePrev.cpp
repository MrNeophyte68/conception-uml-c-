//
// Created by akhan on 2026-04-02.
//

#include "Strategy/ModePrev.h"

std::string ModePrev::getDescription() {
    return "Prevente (-10%)";
}

double ModePrev::calculerPrix(double montant) {
    return montant*0.90;
}