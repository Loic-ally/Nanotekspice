/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** FlowLatch.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include "Components/Operators/AndGate.hpp"
#include "Components/Operators/Latch.hpp"
#include "Components/Operators/NotGate.hpp"
#include <memory>

namespace nts {
class FlowLatch : public AComponent {
  public:
    FlowLatch();
    ~FlowLatch() override = default;
    void simulate(std::size_t tick) override;
    nts::Tristate compute(std::size_t pin) override;

  private:
    std::unique_ptr<IComponent> _latch;
    std::unique_ptr<IComponent> _notGate;
    std::unique_ptr<IComponent> _setGate;
    std::unique_ptr<IComponent> _resetGate;
};
} // namespace nts
