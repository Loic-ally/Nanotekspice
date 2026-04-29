/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** FlowLatch.cpp
*/

#include "Components/Operators/FlowLatch.hpp"
#include "Components/Operators/AndGate.hpp"
#include "Components/Operators/Latch.hpp"
#include "Components/Operators/NotGate.hpp"
#include <memory>

namespace nts {

/**
 * @brief Construct a new Flow Latch:: Flow Latch object
 *
 */
FlowLatch::FlowLatch() : AComponent("FlowLatch", 4) {

    _latch = std::make_unique<Latch>();
    _notGate = std::make_unique<NotGate>();
    _setGate = std::make_unique<AndGate>();
    _resetGate = std::make_unique<AndGate>();

    _notGate->setLink(1, *this, 1, false);

    _setGate->setLink(1, *this, 1, false);
    _setGate->setLink(2, *this, 2, false);

    _resetGate->setLink(1, *_notGate, 2, false);
    _resetGate->setLink(2, *this, 2, false);

    _latch->setLink(1, *_setGate, 3, false);
    _latch->setLink(2, *_resetGate, 3, false);
}

/**
 * @brief Simulate the Flow Latch for a given tick
 *
 * @param tick The current simulation tick
 */
void FlowLatch::simulate(std::size_t tick) {
    _latch->simulate(tick);
}

/**
 * @brief Compute the output of the Flow Latch for a given pin
 *
 * @param pin The pin number to compute
 * @return Tristate The computed value of the pin
 */
Tristate FlowLatch::compute(std::size_t pin) {
    if (pin == 3)
        return _latch->compute(3);
    if (pin == 4)
        return _latch->compute(4);
    return AComponent::compute(pin);
}

} // namespace nts
