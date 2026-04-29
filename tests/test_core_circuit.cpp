#include <criterion/criterion.h>

#include "Circuit/Circuit.hpp"
#include "Components/Exception/NtsException.hpp"
#include "Components/Core/AComponent.hpp"

class IndexProbe : public nts::AComponent {
  public:
    IndexProbe() : nts::AComponent("probe", 1, {2}) {}
    ~IndexProbe() override = default;

    std::size_t idx(std::size_t pin) { return getIdx(pin); }
    nts::Tristate compute(std::size_t pin) override
    {
        getIdx(pin);
        return nts::Undefined;
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

Test(acomponent, get_idx_rejects_forbidden_and_out_of_range)
{
    IndexProbe probe;

    cr_assert_eq(probe.idx(1), 0);
    cr_assert_throw(probe.idx(2), nts::InvalidPinError);
    cr_assert_throw(probe.idx(3), nts::InvalidPinError);
    cr_assert_throw(probe.idx(0), nts::InvalidPinError);
}

Test(circuit, simulate_calls_component_once)
{
    nts::Circuit circuit;
    auto comp = std::make_unique<CountingComponent>("in");
    CountingComponent *ptr = comp.get();

    circuit.addComponent("in", std::move(comp));
    circuit.addInput("in");

    circuit.simulate(1);
    cr_assert_eq(ptr->simulateCount, 1);
}

Test(circuit, compute_component_unknown_throws)
{
    nts::Circuit circuit;
    cr_assert_throw(circuit.computeComponent("missing", 1), nts::UnknownComponentNameError);
}
