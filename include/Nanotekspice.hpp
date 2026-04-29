/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Nanotekspice.hpp
*/

#pragma once

#include "Parser/Parser.hpp"
#include "Circuit/Circuit.hpp"
#include "SignalHandler/SignalHandler.hpp"
#include <ostream>
#include <string>

namespace nts
{
    class Nanotekspice
    {
    public:
        explicit Nanotekspice(const std::string &filepath);
        ~Nanotekspice() = default;
        int run();

    private:
        void handleCommand(const std::string &line, bool &running, bool &looping);
        void commandDisplay();
        void commandSimulate();
        void commandSetValue(const std::string &assignment);
        void toggleLoop(bool &looping);
    
        SignalHandler _signalHandler;
        Parser _parser;
        Circuit _circuit;
        std::size_t _tick{0};
    };

    std::ostream &operator<<(std::ostream &os, Tristate value);
}
