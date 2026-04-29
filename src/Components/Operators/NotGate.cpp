#include "Components/Operators/NotGate.hpp"
#include "Components/Core/IComponent.hpp"

namespace nts {
/**
 * @brief Construct a new Not Gate:: Not Gate object
 * 
 */
NotGate::NotGate() : AComponent("NotGate", 2) {};

/**
 * @brief Computes the output of the Not gate for the given pin
 * 
 * @param pin The pin number to compute
 * @return Tristate The result of the Not operation
 */
Tristate NotGate::compute(std::size_t pin) {
    if (pin != 2)
        return AComponent::compute(pin);
    if (_computing.count(pin))
        return getCachedValue(pin);
    _computing.insert(pin);

    Tristate first = getLink(1);
    Tristate result = Undefined;

    if (first == True)
        result = False;
    else if (first == False)
        result = True;

    _computing.erase(pin);
    setCachedValue(pin, result);
    return result;
}
} // namespace nts
