#include <criterion/criterion.h>

#include "Components/Factory/ChipsetFactory.hpp"
#include "Components/Factory/ComponentRegistry.hpp"
#include "Components/Exception/NtsException.hpp"
#include "Components/Tristate/True.hpp"
#include "Nanotekspice.hpp"
#include <sstream>

Test(component_registry, register_and_create)
{
    nts::ComponentRegistry registry;

    registry.registerFactory("dummy", [] { return std::make_unique<nts::TrueComponent>(); });

    cr_assert(registry.exists("dummy"));
    auto comp = registry.create("dummy");
    cr_assert_not_null(comp.get());
    cr_assert_throw(registry.create("missing"), nts::UnknownComponentTypeError);
}

Test(chipset_factory, has_builtins)
{
    nts::ChipsetFactory factory;

    cr_assert(factory.has("input"));
    cr_assert(factory.has("output"));
    cr_assert(factory.has("and"));
    cr_assert(!factory.has("nope"));
}

Test(tristate_stream, outputs_expected_chars)
{
    std::ostringstream oss;

    oss << nts::True;
    oss << nts::False;
    oss << nts::Undefined;

    cr_assert_str_eq(oss.str().c_str(), "10U");
}
