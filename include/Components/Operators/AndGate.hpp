/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** AndGate.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"

namespace nts {
class AndGate : public AComponent {
  public:
    AndGate();
    ~AndGate() override = default;
    Tristate compute(std::size_t pin) override;
};
} // namespace nts
