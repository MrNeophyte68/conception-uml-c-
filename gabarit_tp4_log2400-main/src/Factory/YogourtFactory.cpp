//
// Created by akhan on 2026-04-02.
//
#include "Factory/YogourtFactory.h"

std::unique_ptr<Yogourt> YogourtFactory::createYogourt(const std::string& type) {
    if (type == "nature") {
        return std::make_unique<YogourtNature>();
    } else if (type == "grec") {
        return std::make_unique<YogourtGrec>();
    }

    return nullptr;
}