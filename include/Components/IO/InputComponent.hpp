/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** InputComponent.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"

namespace nts {
class InputComponent : public AComponent {
  public:
    InputComponent();
    ~InputComponent() override = default;
    void simulate(std::size_t tick) override;
    nts::Tristate compute(std::size_t pin) override;
    void setLink(std::size_t pin, nts::IComponent &other,
                 std::size_t otherPin, bool bidirectional = true) override;

  private:
    nts::Tristate _value = nts::Undefined;
    nts::Tristate _next = nts::Undefined;
};
} // namespace nts
