/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** SumGate.cpp
*/

#include "Components/Operators/SumGate.hpp"

namespace nts {

/**
 * @brief Construct a new Sum Gate:: Sum Gate object
 * 
 */
SumGate::SumGate() : AComponent("SumGate", 5) {}

/**
 * @brief Computes the output of the SumGate component for the given pin.
 * 
 * @param pin The pin number to compute.
 * @return Tristate The computed value of the pin.
 */
Tristate SumGate::compute(std::size_t pin) {
    if (pin != 4 && pin != 5)
        return AComponent::compute(pin);
    if (_computing.count(pin))
        return getCachedValue(pin);
    _computing.insert(pin);

    Tristate a = getLink(1);
    Tristate b = getLink(2);
    Tristate c = getLink(3);
    Tristate result = Undefined;

    if (a != Undefined && b != Undefined && c != Undefined) {
        int ai = (a == True ? 1 : 0);
        int bi = (b == True ? 1 : 0);
        int ci = (c == True ? 1 : 0);
        if (pin == 4)
            result = (ai ^ bi ^ ci) ? True : False;
        else
            result = ((ai & bi) | (ci & (ai ^ bi))) ? True : False;
    }

    _computing.erase(pin);
    setCachedValue(pin, result);
    return result;
}

} // namespace nts
