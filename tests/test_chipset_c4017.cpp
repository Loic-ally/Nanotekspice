#include <criterion/criterion.h>

#include "Components/Chipset/C4017.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

Test(chipset_c4017, initial_state_is_q0)
{
    nts::C4017 chip;

    cr_assert_eq(chip.compute(3), nts::True);
    cr_assert_eq(chip.compute(2), nts::False);
    cr_assert_eq(chip.compute(12), nts::True);
}

Test(chipset_c4017, increments_on_rising_edge)
{
    nts::C4017 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(15, f, 1); // reset low
    chip.setLink(13, f, 1); // inhibit low
    chip.setLink(14, t, 1); // clock high

    chip.simulate(0);

    cr_assert_eq(chip.compute(2), nts::True);
    cr_assert_eq(chip.compute(3), nts::False);
}
