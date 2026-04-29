/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4013.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include "Components/Operators/FlipFlop.hpp"
#include <array>
#include <memory>

namespace nts {
class C4013 : public AComponent {
  public:
    C4013();
    ~C4013() override = default;
    void simulate(std::size_t tick) override;
    nts::Tristate compute(std::size_t pin) override;

  private:
    std::array<std::unique_ptr<IComponent>, 2> _ffs;
};
} // namespace nts
