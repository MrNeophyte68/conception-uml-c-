//
// Created by akhan on 2026-04-02.
//

#pragma once
#include <memory>
#include <string>
#include "DecoratorAndPrototype/Yogourt.h"
#include "DecoratorAndPrototype/YogourtGrec.h"
#include "DecoratorAndPrototype/YogourtNature.h"


class YogourtFactory {
    public:
        ~YogourtFactory() = default;
        static std::unique_ptr<Yogourt> createYogourt(const std::string& type);

};
