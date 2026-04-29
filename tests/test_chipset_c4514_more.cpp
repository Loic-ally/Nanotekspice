#include <criterion/criterion.h>

#include "Components/Chipset/C4514.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"
#include "Components/Tristate/Undefined.hpp"

Test(chipset_c4514, inhibit_forces_all_low)
{
    nts::C4514 chip;
    nts::TrueComponent t;

    chip.setLink(23, t, 1); // inhibit high

    cr_assert_eq(chip.compute(11), nts::False);
    cr_assert_eq(chip.compute(6), nts::False);
}

Test(chipset_c4514, enable_undefined_returns_undefined)
{
    nts::C4514 chip;
    nts::FalseComponent f;

    chip.setLink(23, f, 1); // inhibit low

    cr_assert_eq(chip.compute(11), nts::Undefined);
}

Test(chipset_c4514, undefined_latch_bit_propagates)
{
    nts::C4514 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;
    nts::UndefinedComponent u;

    chip.setLink(1, t, 1);   // enable latch
    chip.setLink(23, f, 1);  // inhibit low

    chip.setLink(2, u, 1);   // bit0 undefined
    chip.setLink(3, f, 1);
    chip.setLink(21, f, 1);
    chip.setLink(22, f, 1);

    chip.simulate(0);

    cr_assert_eq(chip.compute(11), nts::Undefined);
}
