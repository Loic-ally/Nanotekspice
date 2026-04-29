/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** QuadBinaryGateChipset.cpp
*/

#include "Components/Chipset/QuadBinaryGateChipset.hpp"
#include <memory>

namespace nts {
template <typename GateType>
/**
 * @brief Construct a new Quad Binary Gate Chipset< Gate Type>:: Quad Binary
 * Gate Chipset object
 *
 * @param name
 */
QuadBinaryGateChipset<GateType>::QuadBinaryGateChipset(const std::string &name)
    : AComponent(name, 12, {7, 14}) {
    constexpr std::array<std::array<std::size_t, 2>, 4> inputPins = {
        {{1, 2}, {5, 6}, {8, 9}, {12, 13}}
    };

    for (std::size_t i = 0; i < inputPins.size(); ++i) {
        _gates[i] = std::make_unique<GateType>();
        _gates[i]->setLink(1, *this, inputPins[i][0], false);
        _gates[i]->setLink(2, *this, inputPins[i][1], false);
    }
}

template <typename GateType>
/**
 * @brief Computes the output of the QuadBinaryGateChipset for the given pin.
 *
 * @param pin The pin number to compute.
 * @return Tristate The computed value of the pin.
 */
Tristate QuadBinaryGateChipset<GateType>::compute(std::size_t pin) {
    return computeFromQuad(pin);
}

template <typename GateType>
/**
 * @brief Simulates all gates in the QuadBinaryGateChipset.
 *
 */
void QuadBinaryGateChipset<GateType>::simulateQuad() {
    for (auto &gate : _gates)
        gate->compute(3);
}

template <typename GateType>
/**
 * @brief Computes the output of the QuadBinaryGateChipset for a given pin.
 *
 * @param pin The pin number to compute.
 * @return Tristate The computed value of the pin.
 */
Tristate QuadBinaryGateChipset<GateType>::computeFromQuad(std::size_t pin) {
    constexpr std::array<std::size_t, 4> outputPins = {3, 4, 10, 11};

    for (std::size_t i = 0; i < outputPins.size(); ++i) {
        if (pin == outputPins[i])
            return _gates[i]->compute(3);
    }
    return getLink(pin);
}

template class QuadBinaryGateChipset<AndGate>;
template class QuadBinaryGateChipset<NandGate>;
template class QuadBinaryGateChipset<NorGate>;
template class QuadBinaryGateChipset<OrGate>;
template class QuadBinaryGateChipset<XorGate>;
} // namespace nts
