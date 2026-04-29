/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** True.cpp
*/

#include "Components/Tristate/True.hpp"

namespace nts
{
    /**
     * @brief Construct a new True Component:: True Component object
     * 
     */
    TrueComponent::TrueComponent() : AComponent("true", 1) {}

    /**
     * @brief Simulates the true component (no operation)
     * 
     */
    void TrueComponent::simulate(std::size_t) {}

    /**
     * @brief Computes the state of the true component at the given pin
     * 
     * @param pin The pin number to compute
     * @return nts::Tristate The state of the true component at the given pin (always True)
     */
    nts::Tristate TrueComponent::compute(std::size_t pin)
    {
        getIdx(pin);
        return nts::True;
    }
}
