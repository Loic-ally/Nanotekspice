#include <criterion/criterion.h>

#include "Components/Factory/ChipsetFactory.hpp"
#include <string>
#include <vector>

Test(chipset_factory, creates_all_registered_components)
{
    nts::ChipsetFactory factory;
    const std::vector<std::string> types = {
        "input", "output", "clock", "true", "false",
        "and", "or", "xor", "not", "nor", "nand",
        "4001", "4011", "4030", "4069", "4071", "4081",
        "4008", "4013", "4017", "4040", "4094",
        "4512", "4514", "2716", "logger"
    };

    for (const auto &type : types) {
        auto comp = factory.createComponent(type);
        cr_assert_not_null(comp.get());
    }
}
