/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Pin index lookup helper implementation
*/

#include "Components/Core/PinLookup.hpp"

namespace nts {
/**
 * @brief Returns the index of a pin inside an ordered pin list.
 *
 * @param pin The pin number to find.
 * @param pins The lookup table of valid output pins.
 * @return int The zero-based index of the pin, or -1 if not found.
 */
int pinIndex(std::size_t pin, std::span<const std::size_t> pins) {
    for (std::size_t i = 0; i < pins.size(); ++i) {
        if (pins[i] == pin)
            return static_cast<int>(i);
    }
    return -1;
}
} // namespace nts
