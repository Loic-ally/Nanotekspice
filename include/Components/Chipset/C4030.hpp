/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4030.hpp
*/

#pragma once

#include "Components/Chipset/QuadBinaryGateChipset.hpp"
#include "Components/Operators/XorGate.hpp"

namespace nts {
class C4030 : public QuadBinaryGateChipset<XorGate> {
  public:
    C4030();
    ~C4030() override = default;
};
} // namespace nts
