#include <criterion/criterion.h>

#include "Circuit/Circuit.hpp"
#include "Components/Core/AComponent.hpp"
#include "Components/Exception/NtsException.hpp"

class SelfLinkComponent : public nts::AComponent {
  public:
    SelfLinkComponent() : nts::AComponent("self", 1) {}
    ~SelfLinkComponent() override = default;

    nts::Tristate compute(std::size_t pin) override
    {
        return nts::AComponent::compute(pin);
    }
};

class CountingComponent : public nts::AComponent {
  public:
    explicit CountingComponent(const std::string &name)
        : nts::AComponent(name, 1)
    {
    }

    void simulate(std::size_t) override { ++simulateCount; }

    nts::Tristate compute(std::size_t pin) override
    {
        getIdx(pin);
        return nts::Undefined;
    }

    int simulateCount = 0;
};

class TrueComponentStub : public nts::AComponent {
  public:
    TrueComponentStub() : nts::AComponent("stub", 1) {}
    nts::Tristate compute(std::size_t pin) override
    {
        getIdx(pin);
        return nts::True;
    }
};

Test(acomponent, recursive_compute_uses_cache)
{
    SelfLinkComponent comp;

    comp.setLink(1, comp, 1);
    cr_assert_eq(comp.compute(1), nts::Undefined);
}

Test(circuit, simulate_deduplicates_components)
{
    nts::Circuit circuit;
    auto comp = std::make_unique<CountingComponent>("dup");
    CountingComponent *ptr = comp.get();

    circuit.addComponent("dup", std::move(comp));
    circuit.addInput("dup");
    circuit.addClock("dup");

    circuit.simulate(0);
    cr_assert_eq(ptr->simulateCount, 1);
}

Test(circuit, compute_component_returns_value)
{
    nts::Circuit circuit;
    auto comp = std::make_unique<TrueComponentStub>();

    circuit.addComponent("ok", std::move(comp));
    cr_assert_eq(circuit.computeComponent("ok", 1), nts::True);
}
