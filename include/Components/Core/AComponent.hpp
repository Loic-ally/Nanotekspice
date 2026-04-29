/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Abstract component with basic wiring helpers
*/

#pragma once

#include "Components/Core/IComponent.hpp"
#include <cstddef>
#include <functional>
#include <list>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace nts {
class AComponent : public IComponent {
  public:
    AComponent(const std::string &name, std::size_t pinCount,
               const std::list<std::size_t> forbiddenPins = {});
    virtual ~AComponent() override = 0;
    void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin,
                 bool bidirectional = true) override;
    const std::string &getName() const;
    void simulate(std::size_t tick) override;
    Tristate compute(std::size_t pin) override;

  protected:
    struct Link {
        std::reference_wrapper<nts::IComponent> component;
        std::size_t otherPin;
    };

    std::string _name;
    std::size_t _nbUsablePin;
    std::vector<std::vector<Link>> _pins;
    const std::vector<std::size_t> _forbiddenPins;

    std::size_t getIdx(std::size_t pin) const;
    Tristate getLink(std::size_t pin);
    Tristate getCachedValue(std::size_t pin);
    void setCachedValue(std::size_t pin, Tristate value);
    std::unordered_map<std::size_t, Tristate> _cachedValues;
    std::unordered_set<std::size_t> _computing;
};
} // namespace nts
