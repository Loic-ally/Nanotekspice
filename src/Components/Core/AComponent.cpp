/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** AComponent.cpp
*/

#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include "Components/Exception/NtsException.hpp"
#include <iostream>
#include <list>
#include <stdexcept>

namespace nts {

/**
 * @brief Destroy the AComponent::AComponent object
 *
 */
AComponent::~AComponent() = default;

/**
 * @brief Construct a new AComponent::AComponent object
 *
 * @param name The name of the component
 * @param pinCount The number of usable pins for the component
 * @param forbiddenPins A list of pin numbers that are not usable for the
 * component
 */
AComponent::AComponent(const std::string &name, std::size_t pinCount,
                       const std::list<std::size_t> forbiddenPins)
    : _name(name), _nbUsablePin(pinCount), _pins(pinCount),
      _forbiddenPins(forbiddenPins.begin(), forbiddenPins.end()) {}

/**
 * @brief Converts a pin index to an internal index, accounting for forbidden
 * pins
 *
 * @param idx The external pin index
 * @return std::size_t The internal index corresponding to the external pin
 * index
 */
std::size_t AComponent::getIdx(std::size_t idx) const {
    std::size_t offset = 1;

    if (idx < 1 || idx > _nbUsablePin + _forbiddenPins.size()) {
        throw InvalidPinError("Pin index " + std::to_string(idx) +
                              " is out of range");
    }
    for (const auto &forbidenPin : _forbiddenPins) {
        if (forbidenPin == idx) {
            throw InvalidPinError("Pin index " + std::to_string(idx) +
                                  " is forbidden");
        }
        if (forbidenPin > idx) {
            break;
        }
        offset++;
    }
    return idx - offset;
}

/**
 * @brief Simulates the component for a given tick
 *
 * @param tick The current simulation tick
 */
void AComponent::simulate(std::size_t tick) {
    (void)tick;
};

/**
 * @brief Computes the output of the component for a given pin
 *
 * @param pin The pin number to compute
 * @return Tristate The computed value of the pin
 */
Tristate AComponent::compute(std::size_t pin) {
    if (_computing.count(pin))
        return getCachedValue(pin);
    _computing.insert(pin);
    Tristate result = getLink(pin);
    _computing.erase(pin);
    setCachedValue(pin, result);
    return result;
}

/**
 * @brief Sets a link between this component's pin and another component's pin
 *
 * @param thisPin The pin number on this component
 * @param comp The other component to link to
 * @param otherPin The pin number on the other component
 */
void AComponent::setLink(std::size_t thisPin, IComponent &comp,
                         std::size_t otherPin, bool bidirectional) {
    auto &linksOpt = _pins[getIdx(thisPin)];
    linksOpt.push_back(Link{std::ref(comp), otherPin});
    if (bidirectional)
        comp.setLink(otherPin, *this, thisPin, false);
};

/**
 * @brief Retrieves the value linked to a given pin
 *
 * @param pin The pin number to retrieve the value from
 * @return Tristate The value of the linked pin or Undefined if no link exists
 */
Tristate AComponent::getLink(std::size_t pin) {
    auto &links = _pins[getIdx(pin)];

    if (links.empty())
        return Undefined;
    Tristate resolved = Undefined;
    for (const auto &link : links) {
        Tristate value = link.component.get().compute(link.otherPin);
        if (value != Undefined)
            resolved = value;
    }
    return resolved;
}

/**
 * @brief Gets a cached value for a given pin
 *
 * @param pin The pin number to retrieve the cached value for
 * @return Tristate The cached value, or Undefined if not cached
 */
Tristate AComponent::getCachedValue(std::size_t pin) {
    auto it = _cachedValues.find(pin);

    if (it == _cachedValues.end())
        return Undefined;
    return it->second;
}

/**
 * @brief Sets a cached value for a given pin
 *
 * @param pin The pin number to set the cached value for
 * @param value The value to cache
 */
void AComponent::setCachedValue(std::size_t pin, Tristate value) {
    _cachedValues[pin] = value;
}

/**
 * @brief Gets the name of the component
 *
 * @return const std::string& The name of the component
 */
const std::string &AComponent::getName() const {
    return _name;
}

} // namespace nts
