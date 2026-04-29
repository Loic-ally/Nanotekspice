/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** InputComponent.cpp
*/

#include "Components/IO/InputComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include <iostream>

namespace nts {
/**
 * @brief Construct a new Input Component:: Input Component object
 *
 */
InputComponent::InputComponent() : AComponent("input", 1) {}

/**
 * @brief Simulates the input component (no operation)
 *
 */
void InputComponent::simulate(std::size_t tick) {
    (void)tick;
    _value = _next;
}

/**
 * @brief Computes the state of the input component at the given pin
 *
 * @param pin The pin number to compute
 * @return Tristate The state of the input component at the given pin
 */
Tristate InputComponent::compute(std::size_t pin) {
    getIdx(pin);
    return _value;
}

/**
 * @brief Get the next value of the input
 *
 * @param pin The pin number to put the value from
 * @param other The component to get the value from
 * @param otherPin The pin number to get the value from the other component
 */
void InputComponent::setLink(std::size_t pin, nts::IComponent &other,
                             std::size_t otherPin, bool bidirectional) {
    getIdx(pin);
    _next = other.compute(otherPin);
    if (bidirectional)
        other.setLink(otherPin, *this, pin, false);
};
} // namespace nts
