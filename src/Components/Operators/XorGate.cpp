#include "Components/Operators/XorGate.hpp"
#include "Components/Core/IComponent.hpp"

namespace nts {

/**
 * @brief Construct a new Xor Gate:: Xor Gate object
 * 
 */
XorGate::XorGate() : AComponent("XorGate", 3) {};

/**
 * @brief Computes the output of the Xor gate for the given pin
 * 
 * @param pin The pin number to compute
 * @return Tristate The result of the Xor operation
 */
Tristate XorGate::compute(std::size_t pin) {
    if (pin != 3)
        return AComponent::compute(pin);
    if (_computing.count(pin))
        return getCachedValue(pin);
    _computing.insert(pin);

    Tristate first = getLink(1);
    Tristate second = getLink(2);
    Tristate result = Undefined;

    if (first != Undefined && second != Undefined)
        result = (first == second) ? False : True;

    _computing.erase(pin);
    setCachedValue(pin, result);
    return result;
}
} // namespace nts
