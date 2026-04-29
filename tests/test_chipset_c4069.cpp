#include <criterion/criterion.h>

#include "Components/Chipset/C4069.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

Test(chipset_c4069, inverter_outputs)
{
    nts::C4069 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(1, t, 1);
    cr_assert_eq(chip.compute(2), nts::False);

    chip.setLink(13, f, 1);
    cr_assert_eq(chip.compute(12), nts::True);
}
