#include <criterion/criterion.h>

#include "Components/Chipset/C4040.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

Test(chipset_c4040, reset_outputs_and_switch_cases)
{
    nts::C4040 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(11, t, 1); // reset high
    chip.setLink(10, f, 1); // clock low
    chip.simulate(0);

    cr_assert_eq(chip.compute(9), nts::False);
    cr_assert_eq(chip.compute(7), nts::False);
    cr_assert_eq(chip.compute(6), nts::False);
    cr_assert_eq(chip.compute(5), nts::False);
    cr_assert_eq(chip.compute(3), nts::False);
    cr_assert_eq(chip.compute(2), nts::False);
    cr_assert_eq(chip.compute(4), nts::False);
    cr_assert_eq(chip.compute(13), nts::False);
    cr_assert_eq(chip.compute(12), nts::False);
    cr_assert_eq(chip.compute(14), nts::False);
    cr_assert_eq(chip.compute(15), nts::False);
    cr_assert_eq(chip.compute(1), nts::False);

    cr_assert_eq(chip.compute(10), nts::False);
}
