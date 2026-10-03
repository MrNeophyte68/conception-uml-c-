//
// Created by akhan on 2026-04-02.
//
#include "Strategy/ModePoly.h"

std::string ModePoly::getDescription() {
    return "Coupon Poly (-2.00)";
}

double ModePoly::calculerPrix(double montant) {
    return montant-2.00;
}