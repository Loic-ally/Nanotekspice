/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Logger.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"

namespace nts
{
    class Logger : public AComponent
    {
    public:
        Logger();
        ~Logger() override = default;
        void simulate(std::size_t tick) override;
        nts::Tristate compute(std::size_t pin) override;

    private:
        nts::Tristate _lastClock = nts::Undefined;
    };
}
