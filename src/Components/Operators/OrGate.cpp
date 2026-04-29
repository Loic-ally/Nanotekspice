#include "Components/Operators/OrGate.hpp"
#include "Components/Core/IComponent.hpp"

namespace nts {
/**
 * @brief Construct a new Or Gate:: Or Gate object
 * 
 */
OrGate::OrGate() : AComponent("OrGate", 3) {};

/**
 * @brief Computes the output of the Or gate for the given pin
 * 
 * @param pin The pin number to compute
 * @return Tristate The result of the Or operation
 */
Tristate OrGate::compute(std::size_t pin) {
    if (pin != 3)
        return AComponent::compute(pin);
    if (_computing.count(pin))
        return getCachedValue(pin);
    _computing.insert(pin);

    Tristate first = getLink(1);
    Tristate result = Undefined;

    if (first == True) {
        result = True;
    } else {
        Tristate second = getLink(2);
        if (second == True)
            result = True;
        else if (first == False && second == False)
            result = False;
        else
            result = Undefined;
    }

    _computing.erase(pin);
    setCachedValue(pin, result);
    return result;
}
} // namespace nts
