/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Circuit.hpp
*/

#pragma once

#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace nts {
class Circuit : public AComponent {
  public:
    Circuit();
    ~Circuit() override = default;
    Circuit(const Circuit &) = delete;
    Circuit(Circuit &&) noexcept = default;
    void addComponent(const std::string &name,
                      std::unique_ptr<nts::IComponent> component);
    void simulate(std::size_t tick) override;
    nts::Tristate computeComponent(const std::string &name, std::size_t pin);
    bool hasComponent(const std::string &name) const;
    nts::IComponent &getComponent(const std::string &name);
    const nts::IComponent &getComponent(const std::string &name) const;
    const std::unordered_map<std::string, std::unique_ptr<nts::IComponent>> &
    getComponents() const;
    void addInput(std::string name);
    void addOutput(std::string name);
    void addClock(std::string name);
    const std::vector<nts::IComponent*> &getInputs() const;
    const std::vector<nts::IComponent*> &getOutputs() const;
    const std::vector<nts::IComponent*> &getClocks() const;

  private:
    std::unordered_map<std::string, std::unique_ptr<nts::IComponent>>
        _components;
    std::vector<std::string> _componentOrder;
    std::vector<nts::IComponent*> _inputs;
    std::vector<nts::IComponent*> _outputs;
    std::vector<nts::IComponent*> _clocks;
};
} // namespace nts
