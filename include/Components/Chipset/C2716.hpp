/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C2716.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>

namespace nts {
class C2716 : public AComponent {
  public:
    C2716();
    ~C2716() override = default;
    void simulate(std::size_t tick) override;
    nts::Tristate compute(std::size_t pin) override;

  private:
    int _address;
    std::array<std::uint8_t, 2048> _data;
};
} // namespace nts
