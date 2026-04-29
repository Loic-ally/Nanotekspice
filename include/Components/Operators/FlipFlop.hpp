/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** FlipFlop.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"
#include "Components/Operators/NotGate.hpp"

namespace nts {

class FlipFlop : public AComponent {
  public:
    FlipFlop();
    ~FlipFlop() override = default;
    void simulate(std::size_t tick) override;
    nts::Tristate compute(std::size_t pin) override;

  private:
    NotGate _dataNot;
    nts::Tristate _output = nts::Undefined;
    nts::Tristate _invertedOutput = nts::Undefined;
    nts::Tristate _lastClock = nts::Undefined;
};

} // namespace nts
