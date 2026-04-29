/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4017.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"

namespace nts {
class C4017 : public AComponent {
  public:
    C4017();
    ~C4017() override = default;
    void simulate(std::size_t tick) override;
    nts::Tristate compute(std::size_t pin) override;

  private:
    std::size_t _counter = 0;
    nts::Tristate _lastClock = nts::Undefined;
    nts::Tristate _lastInhibit = nts::Undefined;
    int outputIndex(std::size_t pin) const;
};
} // namespace nts
