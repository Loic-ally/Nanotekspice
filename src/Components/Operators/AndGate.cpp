
#include "Components/Operators/AndGate.hpp"
#include "Components/Core/IComponent.hpp"

namespace nts {

/**
 * @brief Construct a new And Gate:: And Gate object
 *
 */
AndGate::AndGate() : AComponent("AndGate", 3) {};

/**
 * @brief Computes the output of the And gate for the given pin
 *
 * @param pin The pin number to compute
 * @return Tristate The result of the And operation
 */
Tristate AndGate::compute(std::size_t pin) {
    if (pin != 3)
        return AComponent::compute(pin);
    if (_computing.count(pin))
        return getCachedValue(pin);
    _computing.insert(pin);

    Tristate first = getLink(1);
    Tristate result = Undefined;

    if (first == False) {
        result = False;
    } else {
        Tristate second = getLink(2);
        if (second == False)
            result = False;
        else if (first == True && second == True)
            result = True;
        else
            result = Undefined;
    }

    _computing.erase(pin);
    setCachedValue(pin, result);
    return result;
}
} // namespace nts
