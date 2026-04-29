/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4081.hpp
*/

#pragma once

#include "Components/Chipset/QuadBinaryGateChipset.hpp"
#include "Components/Operators/AndGate.hpp"

namespace nts {
class C4081 : public QuadBinaryGateChipset<AndGate> {
  public:
    C4081();
    ~C4081() override = default;
};
} // namespace nts
