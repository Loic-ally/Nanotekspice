/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4040.hpp
*/

#pragma once

#include "Components/Chipset/C4013.hpp"
#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include "Components/Tristate/False.hpp"
#include <array>
#include <memory>

namespace nts {
class C4040 : public AComponent {
  public:
    C4040();
    ~C4040() override = default;
    void simulate(std::size_t tick) override;
    nts::Tristate compute(std::size_t pin) override;

  private:
    // std::array<C4013, 6> _flipflopList;
    std::array<std::unique_ptr<IComponent>, 6> _flipflopList;
    std::unique_ptr<IComponent> _false;
    std::unique_ptr<IComponent> _not;
};

} // namespace nts
