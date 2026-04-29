#include "Circuit/Circuit.hpp"
#include "Components/Exception/NtsException.hpp"
#include <iostream>
#include <unordered_set>
#include <utility>

namespace nts {

/**
 * @brief Construct a new Circuit:: Circuit object
 * 
 */
Circuit::Circuit() : AComponent("circuit", 0) {}

/**
 * @brief Adds a component to the circuit
 * 
 * @param name The name of the component
 * @param component The component to add
 */
void Circuit::addComponent(const std::string &name,
                           std::unique_ptr<nts::IComponent> component) {
    auto it = _components.find(name);
    if (it != _components.end()) {
        it->second = std::move(component);
        return;
    }
    _componentOrder.push_back(name);
    _components[name] = std::move(component);
}

/**
 * @brief Simulates the circuit for a given number of ticks
 * 
 * @param tick The number of ticks to simulate
 */
void Circuit::simulate(std::size_t tick) {
    std::unordered_set<IComponent *> simulated;
    for (auto *clock : _clocks) {
        if (clock != nullptr && simulated.insert(clock).second)
            clock->simulate(tick);
    }
    for (auto *input : _inputs) {
        if (input != nullptr && simulated.insert(input).second)
            input->simulate(tick);
    }
    for (const auto &name : _componentOrder) {
        auto component = _components.find(name);
        if (component == _components.end())
            continue;
        IComponent *ptr = component->second.get();
        if (ptr != nullptr && simulated.insert(ptr).second)
            ptr->simulate(tick);
    }
}

/**
 * @brief Computes the output of a specific component's pin
 * 
 * @param name The name of the component
 * @param pin The pin number to compute
 * @return Tristate The computed value of the pin
 */
Tristate Circuit::computeComponent(const std::string &name, std::size_t pin) {
    auto component = _components.find(name);
    if (component == _components.end())
        throw UnknownComponentNameError(name);
    return component->second->compute(pin);
}

/**
 * @brief Checks if the circuit has a specific component
 * 
 * @param name The name of the component
 * @return true If the component exists in the circuit
 * @return false If the component does not exist in the circuit
 */
bool Circuit::hasComponent(const std::string &name) const {
    return _components.find(name) != _components.end();
};

/**
 * @brief Gets all components in the circuit
 * 
 * @return const std::unordered_map<std::string, std::unique_ptr<nts::IComponent>>& A map of all components in the circuit
 */
const std::unordered_map<std::string, std::unique_ptr<nts::IComponent>> &
Circuit::getComponents() const {
    return _components;
}

/**
 * @brief Gets a specific component from the circuit
 * 
 * @param name The name of the component
 * @return IComponent& A reference to the requested component
 */
IComponent &Circuit::getComponent(const std::string &name) {
    auto component = _components.find(name);
    if (component == _components.end())
        throw UnknownComponentNameError(name);
    return *component->second;
}

/**
 * @brief Gets a specific component from the circuit (const version)
 * 
 * @param name The name of the component
 * @return const IComponent& A reference to the requested component
 */
const IComponent &Circuit::getComponent(const std::string &name) const {
    auto component = _components.find(name);
    if (component == _components.end())
        throw UnknownComponentNameError(name);
    return *component->second;
}

/**
 * @brief Adds an input component to the circuit
 * 
 * @param name The name of the input component
 */
void Circuit::addInput(std::string name) {
    _inputs.push_back(&getComponent(name));
}

/**
 * @brief Adds an output component to the circuit
 * 
 * @param name The name of the output component
 */
void Circuit::addOutput(std::string name) {
    _outputs.push_back(&getComponent(name));
}

/**
 * @brief Adds a clock component to the circuit
 * 
 * @param name The name of the clock component
 */
void Circuit::addClock(std::string name) {
    _clocks.push_back(&getComponent(name));
}

/**
 * @brief Gets all input components in the circuit
 * 
 * @return const std::vector<nts::IComponent *>& A vector of all input components in the circuit
 */
const std::vector<nts::IComponent *> &Circuit::getInputs() const {
    return _inputs;
}

/**
 * @brief Gets all output components in the circuit
 * 
 * @return const std::vector<nts::IComponent *>& A vector of all output components in the circuit
 */
const std::vector<nts::IComponent *> &Circuit::getOutputs() const {
    return _outputs;
}

/**
 * @brief Gets all clock components in the circuit
 * 
 * @return const std::vector<nts::IComponent *>& A vector of all clock components in the circuit
 */
const std::vector<nts::IComponent *> &Circuit::getClocks() const {
    return _clocks;
}

} // namespace nts
