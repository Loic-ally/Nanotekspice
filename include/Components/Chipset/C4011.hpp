/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4011.hpp
*/

#pragma once

#include "Components/Chipset/QuadBinaryGateChipset.hpp"
#include "Components/Operators/NandGate.hpp"

namespace nts {
class C4011 : public QuadBinaryGateChipset<NandGate> {
  public:
    C4011();
    ~C4011() override = default;
};
} // namespace nts
