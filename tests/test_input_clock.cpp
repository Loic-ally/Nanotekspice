#include <criterion/criterion.h>

#include "Components/IO/ClockComponent.hpp"
#include "Components/IO/InputComponent.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

Test(input_component, updates_value_on_simulate)
{
    nts::InputComponent input;
    nts::TrueComponent t;

    cr_assert_eq(input.compute(1), nts::Undefined);

    input.setLink(1, t, 1);
    cr_assert_eq(input.compute(1), nts::Undefined);

    input.simulate(0);
    cr_assert_eq(input.compute(1), nts::True);
}

Test(input_component, can_switch_value_between_ticks)
{
    nts::InputComponent input;
    nts::TrueComponent t;
    nts::FalseComponent f;

    input.setLink(1, t, 1);
    input.simulate(0);
    cr_assert_eq(input.compute(1), nts::True);

    input.setLink(1, f, 1);
    input.simulate(1);
    cr_assert_eq(input.compute(1), nts::False);
}

Test(clock_component, applies_pending_next_value)
{
    nts::ClockComponent clk;
    nts::TrueComponent t;

    cr_assert_eq(clk.compute(1), nts::Undefined);

    clk.setLink(1, t, 1);
    cr_assert_eq(clk.compute(1), nts::Undefined);

    clk.simulate(0);
    cr_assert_eq(clk.compute(1), nts::True);
}

Test(clock_component, toggles_after_first_tick)
{
    nts::ClockComponent clk;
    nts::TrueComponent t;

    clk.setLink(1, t, 1);
    clk.simulate(0);
    cr_assert_eq(clk.compute(1), nts::True);

    clk.simulate(1);
    cr_assert_eq(clk.compute(1), nts::False);
}
