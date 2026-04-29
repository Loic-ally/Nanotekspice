#include <criterion/criterion.h>

#include "Components/Operators/NandGate.hpp"
#include "Components/Operators/NorGate.hpp"
#include "Components/Operators/XorGate.hpp"
#include "Components/Operators/SumGate.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"
#include "Components/Tristate/Undefined.hpp"

Test(nand_gate, truth_table_basic)
{
    nts::NandGate gate;
    nts::TrueComponent t;
    nts::FalseComponent f;

    gate.setLink(1, t, 1);
    gate.setLink(2, t, 1);
    cr_assert_eq(gate.compute(3), nts::False);

    gate.setLink(1, f, 1);
    gate.setLink(2, t, 1);
    cr_assert_eq(gate.compute(3), nts::True);
}

Test(nand_gate, undefined_propagation)
{
    nts::NandGate gate;
    nts::TrueComponent t;
    nts::FalseComponent f;
    nts::UndefinedComponent u;

    gate.setLink(1, t, 1);
    gate.setLink(2, u, 1);
    cr_assert_eq(gate.compute(3), nts::Undefined);

    gate.setLink(1, f, 1);
    gate.setLink(2, u, 1);
    cr_assert_eq(gate.compute(3), nts::True);
}

Test(nor_gate, truth_table_basic)
{
    nts::NorGate gate;
    nts::TrueComponent t;
    nts::FalseComponent f;

    gate.setLink(1, f, 1);
    gate.setLink(2, f, 1);
    cr_assert_eq(gate.compute(3), nts::True);

    gate.setLink(1, t, 1);
    gate.setLink(2, f, 1);
    cr_assert_eq(gate.compute(3), nts::False);
}

Test(nor_gate, undefined_propagation)
{
    nts::NorGate gate;
    nts::FalseComponent f;
    nts::UndefinedComponent u;

    gate.setLink(1, f, 1);
    gate.setLink(2, u, 1);
    cr_assert_eq(gate.compute(3), nts::Undefined);
}

Test(xor_gate, truth_table_basic)
{
    nts::XorGate gate;
    nts::TrueComponent t;
    nts::FalseComponent f;

    gate.setLink(1, t, 1);
    gate.setLink(2, f, 1);
    cr_assert_eq(gate.compute(3), nts::True);

    gate.setLink(1, t, 1);
    gate.setLink(2, t, 1);
    cr_assert_eq(gate.compute(3), nts::False);
}

Test(xor_gate, undefined_propagation)
{
    nts::XorGate gate;
    nts::TrueComponent t;
    nts::UndefinedComponent u;

    gate.setLink(1, t, 1);
    gate.setLink(2, u, 1);
    cr_assert_eq(gate.compute(3), nts::Undefined);
}

Test(sum_gate, computes_sum_and_carry)
{
    nts::SumGate gate;
    nts::TrueComponent t;
    nts::FalseComponent f;

    gate.setLink(1, t, 1);
    gate.setLink(2, t, 1);
    gate.setLink(3, f, 1);

    cr_assert_eq(gate.compute(4), nts::False);
    cr_assert_eq(gate.compute(5), nts::True);
}

Test(sum_gate, computes_another_case)
{
    nts::SumGate gate;
    nts::TrueComponent t;
    nts::FalseComponent f;

    gate.setLink(1, t, 1);
    gate.setLink(2, f, 1);
    gate.setLink(3, f, 1);

    cr_assert_eq(gate.compute(4), nts::True);
    cr_assert_eq(gate.compute(5), nts::False);
}

Test(sum_gate, all_true)
{
    nts::SumGate gate;
    nts::TrueComponent t;

    gate.setLink(1, t, 1);
    gate.setLink(2, t, 1);
    gate.setLink(3, t, 1);

    cr_assert_eq(gate.compute(4), nts::True);
    cr_assert_eq(gate.compute(5), nts::True);
}

Test(sum_gate, undefined_propagation)
{
    nts::SumGate gate;
    nts::TrueComponent t;
    nts::UndefinedComponent u;

    gate.setLink(1, u, 1);
    gate.setLink(2, t, 1);
    gate.setLink(3, t, 1);

    cr_assert_eq(gate.compute(4), nts::Undefined);
    cr_assert_eq(gate.compute(5), nts::Undefined);
}
