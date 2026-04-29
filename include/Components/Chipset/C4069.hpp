/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4069.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include "Components/Operators/NotGate.hpp"
#include <array>
#include <memory>

namespace nts {
class C4069 : public AComponent {
  public:
    C4069();
    ~C4069() override = default;
    nts::Tristate compute(std::size_t pin) override;

  private:
    std::array<std::unique_ptr<IComponent>, 6> _notGateList;
};
} // namespace nts
