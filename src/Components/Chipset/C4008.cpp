/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** C4008.cpp
*/

#include "Components/Chipset/C4008.hpp"
#include "Components/Operators/SumGate.hpp"
#include <memory>

namespace nts {

/**
 * @brief Construct a new C4008::C4008 object
 *
 */
C4008::C4008() : AComponent("C4008", 14, {8, 16}) {
    constexpr std::array<std::size_t, 4> aPins = {7, 5, 3, 1};
    constexpr std::array<std::size_t, 4> bPins = {6, 4, 2, 15};
    for (std::size_t i = 0; i < aPins.size(); ++i) {
        _sumGateList[i] = std::make_unique<SumGate>();
        _sumGateList[i]->setLink(1, *this, aPins[i], false);
        _sumGateList[i]->setLink(2, *this, bPins[i], false);
        if (i == 0)
            _sumGateList[i]->setLink(3, *this, 9, false);
        else
            _sumGateList[i]->setLink(3, *_sumGateList[i - 1], 5, false);
    }
}

/**
 * @brief Computes the output of the C4008 component for the given pin.
 *
 * @param pin The pin number to compute.
 * @return Tristate The computed value of the pin.
 */
Tristate C4008::compute(std::size_t pin) {
    constexpr std::array<std::size_t, 4> sumPins = {10, 11, 12, 13};
    for (std::size_t i = 0; i < sumPins.size(); ++i) {
        if (pin == sumPins[i])
            return _sumGateList[i]->compute(4);
    }
    if (pin == 14)
        return _sumGateList[3]->compute(5);
    return getLink(pin);
}

} // namespace nts
