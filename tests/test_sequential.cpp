#include <criterion/criterion.h>

#include "Components/Operators/FlowLatch.hpp"
#include "Components/Operators/FlipFlop.hpp"
#include "Components/Operators/Latch.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

Test(latch, set_and_reset_paths)
{
    nts::Latch latch;
    nts::TrueComponent t;
    nts::FalseComponent f;

    latch.setLink(1, t, 1);
    latch.setLink(2, f, 1);
    latch.simulate(0);
    cr_assert_eq(latch.compute(3), nts::True);
    cr_assert_eq(latch.compute(4), nts::False);

    latch.setLink(1, f, 1);
    latch.setLink(2, t, 1);
    latch.simulate(1);
    cr_assert_eq(latch.compute(3), nts::False);
    cr_assert_eq(latch.compute(4), nts::True);
}

Test(flow_latch, holds_state_when_disabled)
{
    nts::FlowLatch latch;
    nts::TrueComponent t;
    nts::FalseComponent f;

    latch.setLink(1, t, 1);
    latch.setLink(2, t, 1);
    latch.simulate(0);
    cr_assert_eq(latch.compute(3), nts::True);
    cr_assert_eq(latch.compute(4), nts::False);

    latch.setLink(1, f, 1);
    latch.setLink(2, f, 1);
    latch.simulate(1);
    cr_assert_eq(latch.compute(3), nts::True);
    cr_assert_eq(latch.compute(4), nts::False);
}

Test(flipflop, captures_on_rising_edge)
{
    nts::FlipFlop ff;
    nts::TrueComponent t;
    nts::FalseComponent f;

    ff.setLink(5, t, 1);
    ff.setLink(3, t, 1);
    ff.setLink(4, f, 1);
    ff.setLink(6, f, 1);

    ff.simulate(0);
    cr_assert_eq(ff.compute(1), nts::True);
    cr_assert_eq(ff.compute(2), nts::False);

    ff.setLink(5, f, 1);
    ff.simulate(1);
    cr_assert_eq(ff.compute(1), nts::True);
    cr_assert_eq(ff.compute(2), nts::False);
}

Test(flipflop, reset_and_set)
{
    nts::FlipFlop ff;
    nts::TrueComponent t;
    nts::FalseComponent f;

    ff.setLink(5, t, 1);
    ff.setLink(3, f, 1);
    ff.setLink(4, t, 1);
    ff.setLink(6, f, 1);

    ff.simulate(0);
    cr_assert_eq(ff.compute(1), nts::False);
    cr_assert_eq(ff.compute(2), nts::True);

    ff.setLink(4, f, 1);
    ff.setLink(6, t, 1);
    ff.simulate(1);
    cr_assert_eq(ff.compute(1), nts::True);
    cr_assert_eq(ff.compute(2), nts::False);
}

Test(flipflop, set_and_reset_true_forces_both_true)
{
    nts::FlipFlop ff;
    nts::TrueComponent t;

    ff.setLink(3, t, 1);
    ff.setLink(4, t, 1);
    ff.setLink(6, t, 1);

    ff.simulate(0);
    cr_assert_eq(ff.compute(1), nts::True);
    cr_assert_eq(ff.compute(2), nts::True);
}
