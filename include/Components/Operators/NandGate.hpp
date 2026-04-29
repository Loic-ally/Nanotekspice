/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** NandGate.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include "Components/Operators/AndGate.hpp"
#include "Components/Operators/NotGate.hpp"
#include <memory>

namespace nts {
class NandGate : public AComponent {
  public:
    NandGate();
    ~NandGate() override = default;
    nts::Tristate compute(std::size_t pin) override;

  private:
    std::unique_ptr<IComponent> _andGate;
    std::unique_ptr<IComponent> _notGate;
};
} // namespace nts
