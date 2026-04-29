#include <criterion/criterion.h>

#include "Components/Exception/NtsException.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"
#include "Components/Tristate/Undefined.hpp"

Test(tristate_components, constants_are_returned)
{
    nts::TrueComponent t;
    nts::FalseComponent f;
    nts::UndefinedComponent u;

    cr_assert_eq(t.compute(1), nts::True);
    cr_assert_eq(f.compute(1), nts::False);
    cr_assert_eq(u.compute(1), nts::Undefined);
}

Test(tristate_components, invalid_pin_throws)
{
    nts::TrueComponent t;
    cr_assert_throw(t.compute(2), nts::InvalidPinError);
}
