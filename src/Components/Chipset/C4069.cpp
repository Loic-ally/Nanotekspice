#include "Components/Chipset/C4069.hpp"
#include "Components/Operators/NotGate.hpp"
#include <memory>

namespace nts {

/**
 * @brief Construct a new C4069::C4069 object
 *
 */
C4069::C4069() : AComponent("C4069", 12, {7, 14}) {
    constexpr std::array<std::size_t, 6> inputPins = {1, 3, 5, 9, 11, 13};

    for (std::size_t i = 0; i < inputPins.size(); ++i) {
        _notGateList[i] = std::make_unique<NotGate>();
        _notGateList[i]->setLink(1, *this, inputPins[i], false);
    }
}

/**
 * @brief Compute the output of the C4069 component for a given pin
 *
 * @param pin The pin number to compute
 * @return Tristate The computed value of the pin
 */
Tristate C4069::compute(std::size_t pin) {
    constexpr std::array<std::size_t, 6> outputPins = {2, 4, 6, 8, 10, 12};

    for (std::size_t i = 0; i < outputPins.size(); ++i) {
        if (pin == outputPins[i])
            return _notGateList[i]->compute(2);
    }
    return getLink(pin);
}
} // namespace nts
