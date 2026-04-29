#include <criterion/criterion.h>

#include "Components/Chipset/C4008.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

Test(chipset_c4008, adds_with_carry_chain)
{
    nts::C4008 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(7, t, 1);   // A0 = 1
    chip.setLink(6, t, 1);   // B0 = 1
    chip.setLink(5, f, 1);   // A1 = 0
    chip.setLink(4, f, 1);   // B1 = 0
    chip.setLink(3, f, 1);   // A2 = 0
    chip.setLink(2, f, 1);   // B2 = 0
    chip.setLink(1, f, 1);   // A3 = 0
    chip.setLink(15, f, 1);  // B3 = 0
    chip.setLink(9, f, 1);   // Carry in = 0

    cr_assert_eq(chip.compute(10), nts::False);
    cr_assert_eq(chip.compute(11), nts::True);
    cr_assert_eq(chip.compute(12), nts::False);
    cr_assert_eq(chip.compute(13), nts::False);
    cr_assert_eq(chip.compute(14), nts::False);
}
