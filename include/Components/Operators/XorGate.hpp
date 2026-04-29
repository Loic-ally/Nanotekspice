/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** XorGate.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"

namespace nts {
class XorGate : public AComponent {
  public:
    XorGate();
    ~XorGate() override = default;
    nts::Tristate compute(std::size_t pin) override;
};
} // namespace nts
