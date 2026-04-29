/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** ComponentRegistry.cpp
*/

#include "Components/Factory/ComponentRegistry.hpp"
#include "Components/Exception/NtsException.hpp"

namespace nts
{
    /**
     * @brief Registers a factory function for a given component type
     * 
     * @param type The type of the component
     * @param factory The factory function to create the component
     */
    void ComponentRegistry::registerFactory(const std::string &type, std::function<std::unique_ptr<nts::IComponent>()> factory)
    {
        _factories[type] = std::move(factory);
    }

    /**
     * @brief Creates a new component of the given type
     * 
     * @param type The type of the component to create
     * @return std::unique_ptr<nts::IComponent> A unique pointer to the created component
     */
    std::unique_ptr<nts::IComponent> ComponentRegistry::create(const std::string &type) const
    {
        auto it = _factories.find(type);
        if (it == _factories.end())
            throw UnknownComponentTypeError(type);
        return it->second();
    }

    /**
     * @brief Checks if a component of the given type exists in the registry
     * 
     * @param type The type of the component to check
     * @return true If the component type exists
     * @return false If the component type does not exist
     */
    bool ComponentRegistry::exists(const std::string &type) const
    {
        return _factories.find(type) != _factories.end();
    }
}
