/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4071.hpp
*/

#pragma once

#include "Components/Chipset/QuadBinaryGateChipset.hpp"
#include "Components/Operators/OrGate.hpp"

namespace nts {
class C4071 : public QuadBinaryGateChipset<OrGate> {
  public:
    C4071();
    ~C4071() override = default;
};
} // namespace nts
