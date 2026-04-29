#include "Components/Chipset/C4801.hpp"
#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include <array>
#include <cstddef>
#include <cstdint>

namespace nts {

/**
 * @brief Construct a new C4801::C4801 object
 *
 */
C4801::C4801() : AComponent("C4801", 21, {12, 19, 24}), _address(0) {
    _data.fill(0);
}

/**
 * @brief Simulate the C4801 component for a given tick.
 *
 * @param tick
 */
void C4801::simulate(std::size_t tick) {
    (void)tick;
    constexpr std::array<std::size_t, 10> addressPin = {22, 23, 1, 2, 3,
                                                        4,  5,  6, 7, 8};
    const auto read = getLink(20);
    const auto enable = getLink(18);
    const auto write = getLink(21);

    int newAddress = 0;
    if (enable != False || (read == False && write == False) ||
        (read == True && write == True)) {
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

    if (write == False) {
        int data = 0;
        for (const auto &pin : _inOutPins) {
            data = (data << 1) + (getLink(pin) == True);
        }
        _data.at(_address % 1024) = data;
    }
}

/**
 * @brief Compute the output for a given pin.
 *
 * @param pin The pin number for which to compute the output.
 * @return Tristate
 */
Tristate C4801::compute(std::size_t pin) {
    if (pin < 9 || pin > 17 || pin == 12) {
        return getLink(pin);
    }

    const auto enable = getLink(18);
    const auto read = getLink(20);
    const auto write = getLink(21);

    if (enable != False)
        return Undefined;
    if (read != False || write != True)
        return Undefined;
    std::uint8_t result = _data.at(_address % 1024);

    for (auto it = _inOutPins.rbegin(); it != _inOutPins.rend(); ++it) {
        if (pin != *it) {
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

// C4801::
} // namespace nts
