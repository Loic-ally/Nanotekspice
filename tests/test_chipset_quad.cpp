#include <criterion/criterion.h>

#include "Components/Chipset/C4001.hpp"
#include "Components/Chipset/C4011.hpp"
#include "Components/Chipset/C4030.hpp"
#include "Components/Chipset/C4071.hpp"
#include "Components/Chipset/C4081.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

Test(chipset_c4001, nor_gate_outputs)
{
    nts::C4001 chip;
    nts::FalseComponent f;
    nts::TrueComponent t;

    chip.setLink(1, f, 1);
    chip.setLink(2, f, 1);
    cr_assert_eq(chip.compute(3), nts::True);

    chip.setLink(5, t, 1);
    chip.setLink(6, f, 1);
    cr_assert_eq(chip.compute(4), nts::False);
}

Test(chipset_c4011, nand_gate_outputs)
{
    nts::C4011 chip;
    nts::TrueComponent t;

    chip.setLink(1, t, 1);
    chip.setLink(2, t, 1);
    cr_assert_eq(chip.compute(3), nts::False);
}

Test(chipset_c4030, xor_gate_outputs)
{
    nts::C4030 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(1, t, 1);
    chip.setLink(2, f, 1);
    cr_assert_eq(chip.compute(3), nts::True);
}

Test(chipset_c4071, or_gate_outputs)
{
    nts::C4071 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(1, f, 1);
    chip.setLink(2, t, 1);
    cr_assert_eq(chip.compute(3), nts::True);
}

Test(chipset_c4081, and_gate_outputs)
{
    nts::C4081 chip;
    nts::TrueComponent t;

    chip.setLink(1, t, 1);
    chip.setLink(2, t, 1);
    cr_assert_eq(chip.compute(3), nts::True);
}
