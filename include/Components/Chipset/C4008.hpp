/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4008.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include "Components/Operators/SumGate.hpp"
#include <array>
#include <memory>

namespace nts {
class C4008 : public AComponent {
  public:
    C4008();
    ~C4008() override = default;
    nts::Tristate compute(std::size_t pin) override;

  private:
    std::array<std::unique_ptr<IComponent>, 4> _sumGateList;
};
} // namespace nts
