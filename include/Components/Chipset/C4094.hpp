/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4094.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"
#include <array>
#include <limits>

namespace nts {
class C4094 : public AComponent {
  public:
    C4094();
    ~C4094() override = default;
    void simulate(std::size_t tick) override;
    nts::Tristate compute(std::size_t pin) override;

  private:
    std::array<nts::Tristate, 8> _shift{};
    std::array<nts::Tristate, 8> _latchD{};
    nts::Tristate _qs1 = nts::Tristate::False;
    nts::Tristate _qs2 = nts::Tristate::False;
    nts::Tristate _lastClock = nts::Tristate::Undefined;
    std::size_t _lastTick = std::numeric_limits<std::size_t>::max();
    int outputIndex(std::size_t pin) const;
};
} // namespace nts
