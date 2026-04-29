#include <criterion/criterion.h>

#include "Components/Chipset/C4094.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

Test(chipset_c4094, output_disabled_returns_undefined)
{
    nts::C4094 chip;
    nts::FalseComponent f;

    chip.setLink(15, f, 1); // output enable low

    cr_assert_eq(chip.compute(4), nts::Undefined);
}

Test(chipset_c4094, shift_and_latch)
{
    nts::C4094 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(15, t, 1); // output enable high
    chip.setLink(1, t, 1);  // strobe high
    chip.setLink(2, t, 1);  // data high
    chip.setLink(3, t, 1);  // clock high

    chip.simulate(1);

    cr_assert_eq(chip.compute(4), nts::True);
    cr_assert_eq(chip.compute(5), nts::False);

    chip.setLink(3, f, 1); // clock low
    chip.simulate(2);

    cr_assert_eq(chip.compute(4), nts::True);
}
