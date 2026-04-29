/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** False.cpp
*/

#include "Components/Tristate/False.hpp"

namespace nts
{
    /**
     * @brief Construct a new False Component:: False Component object
     * 
     */
    FalseComponent::FalseComponent() : AComponent("false", 1) {}

    /**
     * @brief Simulates the false component (no operation)
     * 
     */
    void FalseComponent::simulate(std::size_t) {}

    /**
     * @brief Computes the state of the false component at the given pin
     * 
     * @param pin The pin number to compute
     * @return nts::Tristate The state of the false component at the given pin (always False)
     */
    nts::Tristate FalseComponent::compute(std::size_t pin)
    {
        getIdx(pin);
        return nts::False;
    }
}
