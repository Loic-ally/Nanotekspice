/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4512.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"

namespace nts {
class C4512 : public AComponent {
  public:
    C4512();
    ~C4512() override = default;
    Tristate compute(std::size_t pin) override;

  private:
    Tristate getOutput();
};
} // namespace nts
