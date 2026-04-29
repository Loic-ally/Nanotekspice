#include "Components/Chipset/C4512.hpp"
#include <array>

namespace nts {

/**
 * @brief Construct a new C4512::C4512 object
 *
 */
C4512::C4512() : AComponent("C4512", 14, {8, 16}) {}

/**
 * @brief Get the output of the C4512 component
 *
 * @return Tristate The output value of the C4512 component
 */
Tristate C4512::getOutput() {
    Tristate inib = getLink(10);
    Tristate enabled = getLink(15);
    Tristate onePin = getLink(11);
    Tristate twoPin = getLink(12);
    Tristate fourPin = getLink(13);

    if (inib == Undefined || enabled == Undefined || onePin == Undefined ||
        twoPin == Undefined || fourPin == Undefined || enabled == True) {
        return Undefined;
    }
    if (inib == True)
        return False;
    int selectedIndex = 0;
    if (onePin == True)
        selectedIndex |= 1;
    if (twoPin == True)
        selectedIndex |= 2;
    if (fourPin == True)
        selectedIndex |= 4;
    constexpr std::array<std::size_t, 8> dataPins = {1, 2, 3, 4, 5, 6, 7, 9};
    return getLink(dataPins[static_cast<std::size_t>(selectedIndex)]);
}

/**
 * @brief Compute the output of the C4512 component for a given pin
 *
 * @param pin The pin number to compute
 * @return Tristate The computed value of the pin
 */
Tristate C4512::compute(std::size_t pin) {
    if (pin == 14)
        return getOutput();
    return getLink(pin);
}

} // namespace nts
