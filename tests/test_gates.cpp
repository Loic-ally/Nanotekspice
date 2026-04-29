#include <criterion/criterion.h>

#include "Components/Operators/AndGate.hpp"
#include "Components/Operators/NotGate.hpp"
#include "Components/Operators/OrGate.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"
#include "Components/Tristate/Undefined.hpp"

Test(and_gate, truth_table_true_true)
{
    nts::AndGate gate;
    nts::TrueComponent t;

    gate.setLink(1, t, 1);
    gate.setLink(2, t, 1);

    cr_assert_eq(gate.compute(3), nts::True);
}

Test(and_gate, true_false_is_false)
{
    nts::AndGate gate;
    nts::TrueComponent t;
    nts::FalseComponent f;

    gate.setLink(1, t, 1);
    gate.setLink(2, f, 1);

    cr_assert_eq(gate.compute(3), nts::False);
}

Test(and_gate, false_undefined_is_false)
{
    nts::AndGate gate;
    nts::FalseComponent f;
    nts::UndefinedComponent u;

    gate.setLink(1, f, 1);
    gate.setLink(2, u, 1);

    cr_assert_eq(gate.compute(3), nts::False);
}

Test(and_gate, true_undefined_is_undefined)
{
    nts::AndGate gate;
    nts::TrueComponent t;
    nts::UndefinedComponent u;

    gate.setLink(1, t, 1);
    gate.setLink(2, u, 1);

    cr_assert_eq(gate.compute(3), nts::Undefined);
}

Test(or_gate, true_or_undefined_is_true)
{
    nts::OrGate gate;
    nts::TrueComponent t;
    nts::UndefinedComponent u;

    gate.setLink(1, t, 1);
    gate.setLink(2, u, 1);

    cr_assert_eq(gate.compute(3), nts::True);
}

Test(or_gate, false_or_false_is_false)
{
    nts::OrGate gate;
    nts::FalseComponent f;

    gate.setLink(1, f, 1);
    gate.setLink(2, f, 1);

    cr_assert_eq(gate.compute(3), nts::False);
}

Test(or_gate, false_or_undefined_is_undefined)
{
    nts::OrGate gate;
    nts::FalseComponent f;
    nts::UndefinedComponent u;

    gate.setLink(1, f, 1);
    gate.setLink(2, u, 1);

    cr_assert_eq(gate.compute(3), nts::Undefined);
}

Test(not_gate, negates_true)
{
    nts::NotGate gate;
    nts::TrueComponent t;

    gate.setLink(1, t, 1);

    cr_assert_eq(gate.compute(2), nts::False);
}

Test(not_gate, negates_false)
{
    nts::NotGate gate;
    nts::FalseComponent f;

    gate.setLink(1, f, 1);

    cr_assert_eq(gate.compute(2), nts::True);
}

Test(not_gate, undefined_stays_undefined)
{
    nts::NotGate gate;
    nts::UndefinedComponent u;

    gate.setLink(1, u, 1);

    cr_assert_eq(gate.compute(2), nts::Undefined);
}
