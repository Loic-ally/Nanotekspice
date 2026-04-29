/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4801.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"
#include <cstdint>

namespace nts {
class C4801 : public AComponent {
  public:
    C4801();
    ~C4801() override = default;
    void simulate(std::size_t tick) override;
    nts::Tristate compute(std::size_t pin) override;

  private:
    std::array<std::uint8_t, 1024> _data;
    int _address;
    const std::array<std::size_t, 8> _inOutPins = {9,  10, 11, 13,
                                                   14, 15, 16, 17};
};
} // namespace nts