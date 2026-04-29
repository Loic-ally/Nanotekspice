/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4514.cpp
*/

#include "Components/Chipset/C4514.hpp"
#include "Components/Core/PinLookup.hpp"
#include "Components/Operators/FlowLatch.hpp"
#include <memory>

namespace nts {
/**
 * @brief Construct a new C4514::C4514 object
 *
 */
C4514::C4514() : AComponent("C4514", 22, {12, 24}) {
    constexpr std::array<std::size_t, 4> inputPins = {2, 3, 21, 22};

    for (std::size_t i = 0; i < inputPins.size(); ++i) {
        _latches[i] = std::make_unique<FlowLatch>();
        _latches[i]->setLink(1, *this, inputPins[i], false);
        _latches[i]->setLink(2, *this, 1, false);
    }
}

/**
 * @brief Returns the index of the output pin.
 *
 * @param pin The pin number.
 * @return int The index of the output pin, or -1 if not found.
 */
int C4514::outputIndex(std::size_t pin) const {
    constexpr std::array<std::size_t, 16> outputPins = {
        11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15};
    return pinIndex(pin, outputPins);
}

/**
 * @brief Simulates the C4514 behavior for the given tick.
 *
 * @param tick The current simulation tick.
 */
void C4514::simulate(std::size_t tick) {
    for (auto &latch : _latches)
        latch->simulate(tick);
}

/**
 * @brief Computes the output of the C4514 for the given pin.
 *
 * @param pin The pin number to compute.
 * @return Tristate The computed value of the pin.
 */
Tristate C4514::compute(std::size_t pin) {
    int idx = outputIndex(pin);
    if (idx < 0)
        return getLink(pin);
    Tristate inhibit = getLink(23);
    if (inhibit == True)
        return False;
    Tristate enable = getLink(1);
    if (enable == Undefined || inhibit == Undefined)
        return Undefined;
    int selected = 0;
    for (int i = 0; i < 4; i++) {
        Tristate bit = _latches[i]->compute(3);
        if (bit == Undefined)
            return Undefined;
        if (bit == True)
            selected |= (1 << i);
    }
    return (selected == idx) ? True : False;
}
} // namespace nts
