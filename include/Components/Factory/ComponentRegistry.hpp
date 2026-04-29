/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** ComponentRegistry.hpp
*/

#pragma once

#include "Components/Core/IComponent.hpp"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace nts
{
    class ComponentRegistry
    {
    public:
        ComponentRegistry() = default;
        ~ComponentRegistry() = default;
        void registerFactory(const std::string &type, std::function<std::unique_ptr<nts::IComponent>()> factory);
        std::unique_ptr<nts::IComponent> create(const std::string &type) const;
        bool exists(const std::string &type) const;

    private:
        std::unordered_map<std::string, std::function<std::unique_ptr<nts::IComponent>()>> _factories;
    };
}
