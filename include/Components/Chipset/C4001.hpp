/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4001.hpp
*/

#pragma once

#include "Components/Chipset/QuadBinaryGateChipset.hpp"
#include "Components/Operators/NorGate.hpp"

namespace nts {
class C4001 : public QuadBinaryGateChipset<NorGate> {
  public:
    C4001();
    ~C4001() override = default;
    void simulate(std::size_t tick) override;
};
} // namespace nts
