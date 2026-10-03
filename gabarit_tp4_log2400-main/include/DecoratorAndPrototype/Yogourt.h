//
// Created by akhan on 2026-04-02.
//

#pragma once
#include <memory>
#include <string>

class Yogourt {
    public:
        virtual ~Yogourt() = default;
        virtual double getPrice() const = 0;
        virtual std::string getDescription() const = 0;

        //prototype pattern
        virtual std::unique_ptr<Yogourt> clone() const = 0;
};