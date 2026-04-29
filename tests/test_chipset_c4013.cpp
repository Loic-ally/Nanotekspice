#include <criterion/criterion.h>

#include "Components/Chipset/C4013.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

Test(chipset_c4013, set_and_reset_first_ff)
{
    nts::C4013 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(6, t, 1);  // SET
    chip.setLink(4, f, 1);  // RESET
    chip.setLink(3, f, 1);  // CLOCK

    chip.simulate(0);

    cr_assert_eq(chip.compute(1), nts::True);
    cr_assert_eq(chip.compute(2), nts::False);
}

Test(chipset_c4013, reset_second_ff)
{
    nts::C4013 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(10, t, 1); // RESET
    chip.setLink(8, f, 1);  // SET
    chip.setLink(11, f, 1); // CLOCK

    chip.simulate(1);

    cr_assert_eq(chip.compute(13), nts::False);
    cr_assert_eq(chip.compute(12), nts::True);
}
