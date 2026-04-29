/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** ChipsetFactory.cpp
*/

#include "Components/Factory/ChipsetFactory.hpp"
#include "Components/Exception/NtsException.hpp"
#include "Components/IO/ClockComponent.hpp"
#include "Components/IO/InputComponent.hpp"
#include "Components/IO/OutputComponent.hpp"
#include "Components/Operators/AndGate.hpp"
#include "Components/Operators/NandGate.hpp"
#include "Components/Operators/NorGate.hpp"
#include "Components/Operators/NotGate.hpp"
#include "Components/Operators/OrGate.hpp"
#include "Components/Operators/XorGate.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

#include "Components/Chipset/C2716.hpp"
#include "Components/Chipset/C4001.hpp"
#include "Components/Chipset/C4008.hpp"
#include "Components/Chipset/C4011.hpp"
#include "Components/Chipset/C4013.hpp"
#include "Components/Chipset/C4017.hpp"
#include "Components/Chipset/C4030.hpp"
#include "Components/Chipset/C4040.hpp"
#include "Components/Chipset/C4069.hpp"
#include "Components/Chipset/C4071.hpp"
#include "Components/Chipset/C4081.hpp"
#include "Components/Chipset/C4094.hpp"
#include "Components/Chipset/C4512.hpp"
#include "Components/Chipset/C4514.hpp"
#include "Components/Chipset/C4801.hpp"
#include "Components/Chipset/Logger.hpp"

namespace nts {
/**
 * @brief Construct a new Chipset Factory:: Chipset Factory object
 *
 */
ChipsetFactory::ChipsetFactory() {
    registerBuiltins();
}

/**
 * @brief Creates a new component of the given type
 *
 * @param type The type of the component to create
 * @return std::unique_ptr<nts::IComponent> A unique pointer to the created
 * component
 */
std::unique_ptr<nts::IComponent>
ChipsetFactory::createComponent(const std::string &type) const {
    return _registry.create(type);
}

/**
 * @brief Checks if a component of the given type exists in the registry
 *
 * @param type The type of the component to check
 * @return true If the component type exists
 * @return false If the component type does not exist
 */
bool ChipsetFactory::has(const std::string &type) const {
    return _registry.exists(type);
}

/**
 * @brief Returns the component registry
 *
 * @return const ComponentRegistry&
 */
const ComponentRegistry &ChipsetFactory::registry() const {
    return _registry;
}

/**
 * @brief Registers all built-in component factories
 *
 */
void ChipsetFactory::registerBuiltins() {
    _registry.registerFactory(
        "input", [] { return std::make_unique<InputComponent>(); });
    _registry.registerFactory(
        "output", [] { return std::make_unique<OutputComponent>(); });
    _registry.registerFactory(
        "clock", [] { return std::make_unique<ClockComponent>(); });
    _registry.registerFactory("true",
                              [] { return std::make_unique<TrueComponent>(); });
    _registry.registerFactory(
        "false", [] { return std::make_unique<FalseComponent>(); });

    _registry.registerFactory("and",
                              [] { return std::make_unique<AndGate>(); });
    _registry.registerFactory("or", [] { return std::make_unique<OrGate>(); });
    _registry.registerFactory("xor",
                              [] { return std::make_unique<XorGate>(); });
    _registry.registerFactory("not",
                              [] { return std::make_unique<NotGate>(); });
    _registry.registerFactory("nor",
                              [] { return std::make_unique<NorGate>(); });
    _registry.registerFactory("nand",
                              [] { return std::make_unique<NandGate>(); });
    _registry.registerFactory("4001", [] { return std::make_unique<C4001>(); });
    _registry.registerFactory("4011", [] { return std::make_unique<C4011>(); });
    _registry.registerFactory("4030", [] { return std::make_unique<C4030>(); });
    _registry.registerFactory("4069", [] { return std::make_unique<C4069>(); });
    _registry.registerFactory("4071", [] { return std::make_unique<C4071>(); });
    _registry.registerFactory("4081", [] { return std::make_unique<C4081>(); });
    _registry.registerFactory("4008", [] { return std::make_unique<C4008>(); });
    _registry.registerFactory("4013", [] { return std::make_unique<C4013>(); });
    _registry.registerFactory("4017", [] { return std::make_unique<C4017>(); });
    _registry.registerFactory("4040", [] { return std::make_unique<C4040>(); });
    _registry.registerFactory("4094", [] { return std::make_unique<C4094>(); });
    _registry.registerFactory("4512", [] { return std::make_unique<C4512>(); });
    _registry.registerFactory("4514", [] { return std::make_unique<C4514>(); });
    _registry.registerFactory("4801", [] { return std::make_unique<C4801>(); });
    _registry.registerFactory("2716", [] { return std::make_unique<C2716>(); });
    _registry.registerFactory("logger",
                              [] { return std::make_unique<Logger>(); });
}
} // namespace nts
