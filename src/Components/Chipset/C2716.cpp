#include "Components/Chipset/C2716.hpp"
#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <ios>

namespace nts {

/**
 * @brief Construct a new C2716::C2716 object
 *
 */
C2716::C2716() : AComponent("C2716", 21, {12, 21, 24}) {

    // INIT ROM
    _data.fill(0);

    std::ifstream file{"./rom.bin", std::ios::binary};
    if (!file.is_open()) {
        return;
    }
    file.read(reinterpret_cast<char *>(_data.data()), _data.size());
}

/**
 * @brief Simulate the C2716 component for a given tick.
 *
 * @param tick The current simulation tick.
 */
void C2716::simulate(std::size_t tick) {
    (void)tick;
    constexpr std::array<std::size_t, 11> addressPin = {19, 22, 23, 1, 2, 3,
                                                        4,  5,  6,  7, 8};
    const auto read = getLink(20);
    const auto enable = getLink(18);

    int newAddress = 0;
    if (read != False || enable != False) {
        return;
    }

    for (const auto &pin : addressPin) {
        const auto data = getLink(pin);
        if (data == Undefined) {
            return;
        }
        newAddress = (newAddress << 1) + data;
    }
    _address = newAddress;
}

/**
 * @brief Compute the output for a given pin.
 *
 * @param pin The pin number for which to compute the output.
 * @return Tristate The computed value of the pin.
 */
Tristate C2716::compute(std::size_t pin) {
    if (pin < 9 || pin > 17 || pin == 12) {
        return getLink(pin);
    }

    const auto enable = getLink(18);

    if (enable == True) {
        return False;
    }
    if (enable == Undefined) {
        return Undefined;
    }
    constexpr std::array<std::size_t, 8> _outputPins = {9,  10, 11, 13,
                                                        14, 15, 16, 17};
    std::uint8_t result = _data.at(_address % 2048);

    for (const auto &outPin : _outputPins) {
        if (pin != outPin) {
            result = result >> 1;
        } else {
            break;
        }
    }
    if ((result & 1) == 1) {
        return True;
    } else {
        return False;
    }
}

// C2716::
} // namespace nts
