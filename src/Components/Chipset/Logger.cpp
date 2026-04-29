/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Logger.cpp
*/

#include "Components/Chipset/Logger.hpp"
#include <fstream>

namespace nts {

/**
 * @brief Construct a new Logger:: Logger object
 *
 */
Logger::Logger() : AComponent("logger", 10) {}

/**
 * @brief Computes the value of the specified pin
 *
 * @param pin The pin number to compute
 * @return Tristate The computed value of the pin
 */
Tristate Logger::compute(std::size_t pin) {
    if (pin >= 1 && pin <= 10)
        return getLink(pin);
    return Undefined;
}

/**
 * @brief Simulates the behavior of the logger component for a given tick
 *
 * @param tick The current simulation tick
 */
void Logger::simulate(std::size_t tick) {
    (void)tick;
    Tristate curClock = getLink(9);
    Tristate inhibit = getLink(10);

    if (_lastClock != True && curClock == True && inhibit == False) {
        unsigned char byte = 0;
        for (std::size_t i = 1; i <= 8; i++) {
            Tristate bit = getLink(i);
            if (bit == Undefined) {
                if (curClock != Undefined)
                    _lastClock = curClock;
                return;
            }
            if (bit == True)
                byte |= (1 << (i - 1));
        }
        std::ofstream file("./log.bin", std::ios::binary | std::ios::app);
        if (file.is_open())
            file.put(static_cast<char>(byte));
    }
    if (curClock != Undefined)
        _lastClock = curClock;
}

} // namespace nts
