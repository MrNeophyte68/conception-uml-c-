//
// Created by akhan on 2026-04-05.
//
//abstract observer
#pragma once
#include "Miscellaneous/WARNING.h"
class Subscriber {
    protected:
        std::string stockName;
    public:
        Subscriber(const std::string& name) : stockName(name) {}
        virtual ~Subscriber() = default;
        virtual void update(const std::string& name, WARNING type) = 0;
        const std::string& getName() const { return stockName; }
};
