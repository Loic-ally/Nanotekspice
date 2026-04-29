/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4514.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include "Components/Operators/FlowLatch.hpp"
#include <array>
#include <memory>

namespace nts {
class C4514 : public AComponent {
  public:
    C4514();
    ~C4514() override = default;
    void simulate(std::size_t tick) override;
    nts::Tristate compute(std::size_t pin) override;

  private:
    std::array<std::unique_ptr<IComponent>, 4> _latches;
    int outputIndex(std::size_t pin) const;
};
} // namespace nts
