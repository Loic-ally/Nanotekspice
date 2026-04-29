/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Latch.cpp
*/

#include "Components/Operators/Latch.hpp"
#include "Components/Operators/NorGate.hpp"
#include <memory>

namespace nts {

/**
 * @brief Construct a new Latch:: Latch object
 *
 */
Latch::Latch() : AComponent("Latch", 4) {
    for (auto &comp : _norGates) {
        comp = std::make_unique<NorGate>();
    }
    _norGates[0]->setLink(1, *this, 2, false);
    _norGates[0]->setLink(2, *_norGates[1], 3, false);
    _norGates[1]->setLink(1, *this, 1, false);
    _norGates[1]->setLink(2, *_norGates[0], 3, false);
}

/**
 * @brief Simulates the latch behavior for the given tick.
 *
 * @param tick The current simulation tick.
 */
void Latch::simulate(std::size_t tick) {
    (void)tick;
    _norGates[0]->compute(3);
    _norGates[1]->compute(3);
}

/**
 * @brief Computes the output of the latch for the given pin.
 *
 * @param pin The pin number to compute.
 * @return Tristate The computed value of the pin.
 */
Tristate Latch::compute(std::size_t pin) {
    if (pin == 3)
        return _norGates[0]->compute(3);
    if (pin == 4)
        return _norGates[1]->compute(3);
    return AComponent::compute(pin);
}

} // namespace nts
