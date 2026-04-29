/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** FlipFlop.cpp
*/

#include "Components/Operators/FlipFlop.hpp"

namespace nts {

/**
 * @brief Construct a new FlipFlop::FlipFlop object
 *
 */
FlipFlop::FlipFlop() : AComponent("FlipFlop", 6) {
    _dataNot.setLink(1, *this, 5, false);
}

/**
 * @brief Simulates the FlipFlop behavior for the given tick.
 *
 * Pin mapping:
 * 1 = Q, 2 = /Q, 3 = CLOCK, 4 = RESET, 5 = DATA, 6 = SET
 *
 * @param tick The current simulation tick.
 */
void FlipFlop::simulate(std::size_t tick)
{
    (void)tick;
    Tristate set = getLink(6);
    Tristate reset = getLink(4);
    Tristate clock = getLink(3);
    bool risingEdge = (_lastClock != True && clock == True);

    if (set == True && reset == True) {
        _output = True;
        _invertedOutput = True;
    } else if (set == True) {
        _output = True;
        _invertedOutput = False;
    } else if (reset == True) {
        _output = False;
        _invertedOutput = True;
    } else if (risingEdge) {
        _output = getLink(5);
        _invertedOutput = _dataNot.compute(2);
    }
    if (clock != Undefined)
        _lastClock = clock;
}

/**
 * @brief Computes the output of the FlipFlop for the given pin.
 *
 * @param pin The pin number to compute.
 * @return Tristate The computed value of the pin.
 */
nts::Tristate FlipFlop::compute(std::size_t pin)
{
    if (pin == 1)
        return _output;
    if (pin == 2)
        return _invertedOutput;
    return getLink(pin);
}

} // namespace nts
