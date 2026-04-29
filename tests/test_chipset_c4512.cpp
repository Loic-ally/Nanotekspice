#include <criterion/criterion.h>

#include "Components/Chipset/C4512.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

Test(chipset_c4512, selects_input_zero)
{
    nts::C4512 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(15, f, 1); // enable low
    chip.setLink(10, f, 1); // inhibit low
    chip.setLink(11, f, 1); // A0
    chip.setLink(12, f, 1); // A1
    chip.setLink(13, f, 1); // A2
    chip.setLink(1, t, 1);  // D0

    cr_assert_eq(chip.compute(14), nts::True);
}

Test(chipset_c4512, inhibit_forces_low)
{
    nts::C4512 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(15, f, 1); // enable low
    chip.setLink(10, t, 1); // inhibit high
    chip.setLink(11, f, 1);
    chip.setLink(12, f, 1);
    chip.setLink(13, f, 1);

    cr_assert_eq(chip.compute(14), nts::False);
}
