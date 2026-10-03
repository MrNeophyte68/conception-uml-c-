//
// Created by akhan on 2026-04-02.
//

#include "Garniture.h"
#include <string>
#include <iostream>
#include <ostream>

#include "ui/ConsoleColors.h"
#include "Observer/Subscriber.h"

class Granola : public Garniture, public Subscriber {
public:
    Granola(std::unique_ptr<Yogourt> y) : Garniture(std::move(y)), Subscriber("granola") {}
    Granola() : Garniture(nullptr), Subscriber("granola") {}
    std::string getDescription() const override;
    double getPrice() const override;

    //prototype
    std::unique_ptr<Yogourt> clone() const override;

    //observer concrete
    void update(const std::string& name, WARNING type) override;
};
