/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Generic 4x two-input logic-gate chipset helper
*/

#pragma once

#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include "Components/Operators/AndGate.hpp"
#include "Components/Operators/NandGate.hpp"
#include "Components/Operators/NorGate.hpp"
#include "Components/Operators/OrGate.hpp"
#include "Components/Operators/XorGate.hpp"
#include <array>
#include <cstddef>
#include <memory>
#include <string>

namespace nts {
template <typename GateType> class QuadBinaryGateChipset : public AComponent {
  public:
    explicit QuadBinaryGateChipset(const std::string &name);
    Tristate compute(std::size_t pin) override;

  protected:
    void simulateQuad();
    Tristate computeFromQuad(std::size_t pin);

    std::array<std::unique_ptr<IComponent>, 4> _gates;
};
} // namespace nts
