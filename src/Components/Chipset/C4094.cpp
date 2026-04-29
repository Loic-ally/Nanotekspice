/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4094.cpp
*/

#include "Components/Chipset/C4094.hpp"
#include "Components/Core/IComponent.hpp"
#include "Components/Core/PinLookup.hpp"

namespace nts {
/**
 * @brief Construct a new C4094::C4094 object
 *
 */
C4094::C4094() : AComponent("C4094", 14, {8, 16}) {
    _shift.fill(False);
    _latchD.fill(False);
}

/**
 * @brief Returns the index of an output pin in the internal array
 *
 * @param pin The pin number to look up
 * @return int The index in the internal array, or -1 if not found
 */
int C4094::outputIndex(std::size_t pin) const {
    constexpr std::array<std::size_t, 8> outputPins = {4,  5,  6,  7,
                                                       14, 13, 12, 11};
    return pinIndex(pin, outputPins);
}

/**
 * @brief Simulates the behavior of the C4094 chip for the given tick
 *
 * @param tick The current simulation tick
 */
void C4094::simulate(std::size_t tick) {
    if (_lastTick == tick)
        return;
    _lastTick = tick;
    Tristate data = getLink(2);
    Tristate strobe = getLink(1);
    Tristate clock = getLink(3);
    bool risingEdge = (_lastClock != True && clock == True);
    bool fallingEdge = (_lastClock == True && clock == False);

    if (risingEdge) {
        Tristate shiftedOut = _shift[7];
        for (int i = 7; i > 0; i--)
            _shift[i] = _shift[i - 1];
        _shift[0] = data;
        _qs1 = shiftedOut;
    }
    if (fallingEdge)
        _qs2 = _qs1;
    if (strobe == True)
        _latchD = _shift;
    if (clock != Undefined)
        _lastClock = clock;
}

/**
 * @brief Computes the output value for a given pin
 *
 * @param pin The pin number to compute the output for
 * @return Tristate The computed output value
 */
Tristate C4094::compute(std::size_t pin) {
    int idx = outputIndex(pin);
    if (idx >= 0) {
        Tristate outputEnable = getLink(15);
        if (outputEnable != True)
            return Undefined;
        return _latchD[idx];
    }
    if (pin == 9)
        return _qs1;
    if (pin == 10)
        return _qs2;
    return getLink(pin);
}
} // namespace nts
