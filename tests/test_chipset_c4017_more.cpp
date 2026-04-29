#include <criterion/criterion.h>

#include "Components/Chipset/C4017.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

Test(chipset_c4017, reset_after_increment)
{
    nts::C4017 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(15, f, 1); // reset low
    chip.setLink(13, f, 1); // inhibit low
    chip.setLink(14, t, 1); // clock high
    chip.simulate(0);

    cr_assert_eq(chip.compute(2), nts::True); // Q1

    chip.setLink(15, t, 1); // reset high
    chip.simulate(1);

    cr_assert_eq(chip.compute(3), nts::True); // Q0
}

Test(chipset_c4017, inhibit_prevents_increment)
{
    nts::C4017 chip;
    nts::TrueComponent t;

    chip.setLink(13, t, 1); // inhibit high
    chip.setLink(14, t, 1); // clock high
    chip.simulate(0);

    cr_assert_eq(chip.compute(3), nts::True); // still Q0
}

Test(chipset_c4017, increment_on_inhibit_falling_edge)
{
    nts::C4017 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(13, t, 1); // inhibit high
    chip.setLink(14, t, 1); // clock high
    chip.simulate(0);

    chip.setLink(13, f, 1); // inhibit low
    chip.simulate(1);

    cr_assert_eq(chip.compute(2), nts::True); // Q1
}
