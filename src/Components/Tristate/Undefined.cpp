/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Undefined.cpp
*/

#include "Components/Tristate/Undefined.hpp"

namespace nts
{
    /**
     * @brief Construct a new Undefined Component:: Undefined Component object
     * 
     */
    UndefinedComponent::UndefinedComponent() : AComponent("undefined", 1) {}

    /**
     * @brief Simulates the undefined component (no operation)
     * 
     */
    void UndefinedComponent::simulate(std::size_t) {}

    /**
     * @brief Computes the state of the undefined component at the given pin
     * 
     * @param pin The pin number to compute
     * @return nts::Tristate The state of the undefined component at the given pin (always Undefined)
     */
    nts::Tristate UndefinedComponent::compute(std::size_t pin)
    {
        getIdx(pin);
        return nts::Undefined;
    }
}
