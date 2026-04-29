/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4017.cpp
*/

#include "Components/Chipset/C4017.hpp"
#include "Components/Core/IComponent.hpp"
#include "Components/Core/PinLookup.hpp"

namespace nts {
/**
 * @brief Construct a new C4017::C4017 object
 *
 */
C4017::C4017() : AComponent("C4017", 14, {8, 16}) {}

/**
 * @brief Returns the index of the output pin (Q0..Q9).
 *
 * @param pin The pin number.
 * @return int The output index or -1 if not an output.
 */
int C4017::outputIndex(std::size_t pin) const {
    constexpr std::array<std::size_t, 10> outputPins = {3, 2, 4, 7, 10,
                                                        1, 5, 6, 9, 11};
    return pinIndex(pin, outputPins);
}

/**
 * @brief Simulates the C4017 behavior for the given tick.
 *
 * @param tick The current simulation tick.
 */
void C4017::simulate(std::size_t tick) {
    (void)tick;
    Tristate reset = getLink(15);
    Tristate inhibit = getLink(13);
    Tristate clock = getLink(14);
    bool risingEdgeOne =
        (_lastClock != True && clock == True) && inhibit != True;
    bool risingEdgeTwo =
        (_lastInhibit != False && inhibit == False) && clock != False;

    if (reset == True) {
        _counter = 0;
    } else if (risingEdgeOne || risingEdgeTwo) {
        _counter = (_counter + 1) % 10;
    }
    if (clock != Undefined)
        _lastClock = clock;
    if (inhibit != Undefined)
        _lastInhibit = clock;
}

/**
 * @brief Computes the output of the C4017 for the given pin.
 *
 * @param pin The pin number to compute.
 * @return Tristate The computed value of the pin.
 */
nts::Tristate C4017::compute(std::size_t pin) {
    int idx = outputIndex(pin);
    if (idx >= 0)
        return (_counter == static_cast<std::size_t>(idx)) ? True : False;
    if (pin == 12)
        return (_counter < 5) ? True : False;
    return getLink(pin);
}
} // namespace nts
