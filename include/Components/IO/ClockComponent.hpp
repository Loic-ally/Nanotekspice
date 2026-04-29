/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** ClockComponent.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include "Components/Operators/NotGate.hpp"
#include <memory>

namespace nts {
class ClockComponent : public AComponent {
  public:
    ClockComponent();
    ~ClockComponent() override = default;
    void simulate(std::size_t tick) override;
    Tristate compute(std::size_t pin) override;
    void setLink(std::size_t pin, nts::IComponent &other,
                 std::size_t otherPin, bool bidirectional = true) override;

  private:
    Tristate _current = Undefined;
    Tristate _next = Undefined;
    bool _hasPendingNext = false;
    std::unique_ptr<IComponent> _notGate = std::make_unique<NotGate>();
};
} // namespace nts
