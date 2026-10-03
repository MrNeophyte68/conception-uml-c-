//
// Created by akhan on 2026-04-02.
//

#pragma once
#include <string>
#include "Yogourt.h"
#include <memory>

class Garniture : public Yogourt {
    protected:
        std::unique_ptr<Yogourt> wrappedYogourt;

    public:
        Garniture(std::unique_ptr<Yogourt> yogourt) : wrappedYogourt(std::move(yogourt)) {}
};