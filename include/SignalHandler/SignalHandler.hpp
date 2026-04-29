/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** SignalHandler.hpp
*/

#pragma once

#include <csignal>

namespace nts
{
    class SignalHandler
    {
    public:
        SignalHandler() = default;
        ~SignalHandler() = default;

        void setup();
        void reset();
        bool isInterrupted() const;

    private:
        static void handler(int);

        static volatile sig_atomic_t _interrupted;
    };
}
