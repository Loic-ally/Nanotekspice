#include "Components/Operators/NandGate.hpp"
#include "Components/Operators/AndGate.hpp"
#include "Components/Operators/NotGate.hpp"
#include <memory>

namespace nts {

/**
 * @brief Construct a new Nand Gate:: Nand Gate object
 *
 */
NandGate::NandGate() : AComponent("NandGate", 3) {
    _andGate = std::make_unique<AndGate>();
    _notGate = std::make_unique<NotGate>();

    _andGate->setLink(1, *this, 1, false);
    _andGate->setLink(2, *this, 2, false);
    _notGate->setLink(1, *_andGate, 3, false);
    setLink(3, *_notGate, 2, false);
};

/**
 * @brief Compute the output of the Nand Gate for a given pin
 *
 * @param pin The pin number to compute
 * @return Tristate The computed value of the pin
 */
Tristate NandGate::compute(std::size_t pin) {
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
