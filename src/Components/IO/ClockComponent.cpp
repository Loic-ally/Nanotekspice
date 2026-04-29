/*
** EPITECH PROJECT, 2025
** NANOTEKSPICE
** File description:
** Clock.cpp
*/

#include "Components/IO/ClockComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include "Components/Exception/NtsException.hpp"

namespace nts {

/**
 * @brief Construct a new Clock Component:: Clock Component object
 * 
 */
ClockComponent::ClockComponent() : AComponent("clock", 1) {}

/**
 * @brief Compute the value of the specified pin
 *
 * @param pin The pin number to compute
 * @return Tristate The value of the pin
 */
Tristate ClockComponent::compute(std::size_t pin) {
    getIdx(pin);
    return _current;
}

/**
 * @brief Simulate the clock by toggling its current state
 *
 * @param tick The current simulation tick
 */
void ClockComponent::simulate(std::size_t tick) {
    (void)tick;

    if (_hasPendingNext) {
        _current = _next;
        _hasPendingNext = false;
        return;
    }
    if (_current == Undefined)
        return;
    _current = _current == True ? False : True;
}

/**
 * @brief Sets the link between this clock component and another component
 * 
 * @param pin The pin number of this clock component
 * @param other The other component to link to
 * @param otherPin The pin number of the other component
 */
void ClockComponent::setLink(std::size_t pin, nts::IComponent &other,
                             std::size_t otherPin, bool bidirectional) {
    getIdx(pin);
    _next = other.compute(otherPin);
    _hasPendingNext = true;
    if (bidirectional)
        other.setLink(otherPin, *this, pin, false);
}

} // namespace nts
