#include <criterion/criterion.h>

#include "Components/Chipset/C4001.hpp"
#include "Components/Tristate/True.hpp"

Test(chipset_quad, non_output_pin_returns_link)
{
    nts::C4001 chip;
    nts::TrueComponent t;

    chip.setLink(1, t, 1);
    cr_assert_eq(chip.compute(1), nts::True);
}
