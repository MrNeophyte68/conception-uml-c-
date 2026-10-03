//
// Created by akhan on 2026-04-02.
//

#include "Garniture.h"
#include <string>
#include <iostream>
#include <ostream>

#include "Observer/Subscriber.h"
#include "ui/ConsoleColors.h"

class Chocolat : public Garniture, public Subscriber {
public:
    //for decorator
    Chocolat(std::unique_ptr<Yogourt> y) : Garniture(std::move(y)), Subscriber("chocolat") {}
    //for factory
    Chocolat() : Garniture(nullptr), Subscriber("chocolat") {}
    std::string getDescription() const override;
    double getPrice() const override;

    //prototype
    std::unique_ptr<Yogourt> clone() const override;

    //observer concrete
    void update(const std::string& name, WARNING type) override;
};
