#include <criterion/criterion.h>

#include "Components/Chipset/C4094.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"

Test(chipset_c4094, qs1_qs2_after_shift)
{
    nts::C4094 chip;
    nts::TrueComponent t;
    nts::FalseComponent f;

    chip.setLink(15, t, 1); // output enable high
    chip.setLink(1, f, 1);  // strobe low
    chip.setLink(2, t, 1);  // data high

    std::size_t tick = 0;
    for (int i = 0; i < 9; ++i) {
        chip.setLink(3, t, 1); // clock high
        chip.simulate(++tick);
        chip.setLink(3, f, 1); // clock low
        chip.simulate(++tick);
    }

    cr_assert_eq(chip.compute(9), nts::True);
    cr_assert_eq(chip.compute(10), nts::True);
}
