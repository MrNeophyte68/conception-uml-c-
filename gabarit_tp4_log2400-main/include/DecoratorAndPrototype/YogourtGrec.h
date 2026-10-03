//
// Created by akhan on 2026-04-02.
//

#pragma once
#include "Yogourt.h"
#include "Observer/Subscriber.h"
#include <iostream>
#include <ostream>

#include "ui/ConsoleColors.h"
class YogourtGrec : public Yogourt, public Subscriber {
    public:
    YogourtGrec() : Subscriber("grec") {}
    double getPrice() const override;
    std::string getDescription() const override;

    //prototype
    std::unique_ptr<Yogourt> clone() const override;

    //observer concrete
    void update(const std::string& name, WARNING type) override;
};
