//
// Created by akhan on 2026-04-02.
//

#pragma once
#include "Garniture.h"
#include <string>
#include <iostream>
#include <ostream>

#include "ui/ConsoleColors.h"
#include "Observer/Subscriber.h"

class Miel : public Garniture, public Subscriber {
    public:
        Miel(std::unique_ptr<Yogourt> y) : Garniture(std::move(y)), Subscriber("miel") {}
        Miel() : Garniture(nullptr), Subscriber("miel") {}
        std::string getDescription() const override;
        double getPrice() const override;

        //prototype
        std::unique_ptr<Yogourt> clone() const override;

        //observer concrete
        void update(const std::string& name, WARNING type) override;
};
