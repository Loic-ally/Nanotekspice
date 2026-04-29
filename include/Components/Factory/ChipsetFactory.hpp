/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** ChipsetFactory.hpp
*/

#pragma once

#include "Components/Factory/ComponentRegistry.hpp"
#include <memory>
#include <string>

namespace nts {
class ChipsetFactory {
  public:
    ChipsetFactory();
    ~ChipsetFactory() = default;
    std::unique_ptr<nts::IComponent>
    createComponent(const std::string &type) const;
    bool has(const std::string &type) const;
    const ComponentRegistry &registry() const;

  private:
    ComponentRegistry _registry;
    void registerBuiltins();
};
} // namespace nts
