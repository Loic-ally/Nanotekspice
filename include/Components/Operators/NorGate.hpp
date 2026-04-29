/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** NorGate.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"
#include "Components/Operators/NotGate.hpp"
#include "Components/Operators/OrGate.hpp"
#include <memory>

namespace nts {
class NorGate : public AComponent {
  public:
    NorGate();
    ~NorGate() override = default;
    nts::Tristate compute(std::size_t pin) override;

  private:
    std::unique_ptr<IComponent> _orGate;
    std::unique_ptr<IComponent> _notGate;
};
} // namespace nts
