#include <criterion/criterion.h>

#include "Components/Chipset/C4512.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

Test(chipset_c4512, enable_high_returns_undefined)
{
    nts::C4512 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(15, t, 1); // enable high
    chip.setLink(10, f, 1); // inhibit low
    chip.setLink(11, f, 1);
    chip.setLink(12, f, 1);
    chip.setLink(13, f, 1);

    cr_assert_eq(chip.compute(14), nts::Undefined);
}

Test(chipset_c4512, undefined_select_returns_undefined)
{
    nts::C4512 chip;
    nts::FalseComponent f;

    chip.setLink(15, f, 1); // enable low
    chip.setLink(10, f, 1); // inhibit low
    chip.setLink(11, f, 1);
    chip.setLink(12, f, 1);
    // pin 13 left undefined

    cr_assert_eq(chip.compute(14), nts::Undefined);
}
