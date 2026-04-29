/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4013.cpp
*/

#include "Components/Chipset/C4013.hpp"
#include "Components/Operators/FlipFlop.hpp"
#include <iostream>
#include <memory>

namespace nts {

/**
 * @brief Construct a new C4013::C4013 object
 *
 */
C4013::C4013() : AComponent("C4013", 12, {7, 14}) {
    for (auto &flipflop : _ffs) {
        flipflop = std::make_unique<FlipFlop>();
    }

    _ffs[0]->setLink(3, *this, 3, false);
    _ffs[0]->setLink(4, *this, 4, false);
    _ffs[0]->setLink(5, *this, 5, false);
    _ffs[0]->setLink(6, *this, 6, false);

    _ffs[1]->setLink(3, *this, 11, false);
    _ffs[1]->setLink(4, *this, 10, false);
    _ffs[1]->setLink(5, *this, 9, false);
    _ffs[1]->setLink(6, *this, 8, false);
}

/**
 * @brief Simulates the C4013 behavior for the given tick.
 *
 * @param tick The current simulation tick.
 */
void C4013::simulate(std::size_t tick) {
    _ffs[0]->simulate(tick);
    _ffs[1]->simulate(tick);
}

/**
 * @brief Computes the output of the C4013 for the given pin.
 *
 * @param pin The pin number to compute.
 * @return Tristate The computed value of the pin.
 */
nts::Tristate C4013::compute(std::size_t pin) {
    switch (pin) {
    case 1:
        return _ffs[0]->compute(1);
    case 2:
        return _ffs[0]->compute(2);
    case 12:
        return _ffs[1]->compute(2);
    case 13:
        return _ffs[1]->compute(1);
    default:
        return getLink(pin);
    }
}

} // namespace nts
