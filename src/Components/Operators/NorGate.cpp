#include "Components/Operators/NorGate.hpp"
#include "Components/Operators/OrGate.hpp"

namespace nts {

/**
 * @brief Construct a new Nor Gate:: Nor Gate object
 *
 */
NorGate::NorGate() : AComponent("NorGate", 3) {
    _orGate = std::make_unique<OrGate>();
    _notGate = std::make_unique<NotGate>();

    _orGate->setLink(1, *this, 1, false);
    _orGate->setLink(2, *this, 2, false);
    _notGate->setLink(1, *_orGate, 3, false);
    setLink(3, *_notGate, 2, false);
};

/**
 * @brief Compute the output of the Nor Gate for a given pin
 *
 * @param pin The pin number to compute
 * @return Tristate The computed value of the pin
 */
Tristate NorGate::compute(std::size_t pin) {
    if (pin != 3)
        return AComponent::compute(pin);

    if (_computing.count(pin))
        return getCachedValue(pin);
    _computing.insert(pin);

    Tristate result = _notGate->compute(2);

    _computing.erase(pin);
    setCachedValue(pin, result);
    return result;
}

} // namespace nts
