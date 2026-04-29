#include <criterion/criterion.h>

#include "Components/Chipset/C4514.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

Test(chipset_c4514, selects_one_output)
{
    nts::C4514 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(1, t, 1);   // enable latch
    chip.setLink(23, f, 1);  // inhibit low

    chip.setLink(2, t, 1);   // bit0 = 1
    chip.setLink(3, f, 1);   // bit1 = 0
    chip.setLink(21, t, 1);  // bit2 = 1
    chip.setLink(22, f, 1);  // bit3 = 0

    chip.simulate(0);

    cr_assert_eq(chip.compute(6), nts::True);  // index 5
    cr_assert_eq(chip.compute(11), nts::False);
}
