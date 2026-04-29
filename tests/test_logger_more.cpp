#include <criterion/criterion.h>

#include "Components/Chipset/Logger.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"
#include "Components/Tristate/Undefined.hpp"
#include <cstdio>
#include <fstream>

static bool fileExists(const char *path)
{
    std::ifstream in(path, std::ios::binary);
    return in.is_open();
}

Test(chipset_logger, inhibit_prevents_write)
{
    std::remove("./log.bin");

    nts::Logger logger;
    nts::TrueComponent t;
    nts::FalseComponent f;

    logger.setLink(1, f, 1);
    logger.setLink(2, f, 1);
    logger.setLink(3, f, 1);
    logger.setLink(4, f, 1);
    logger.setLink(5, f, 1);
    logger.setLink(6, f, 1);
    logger.setLink(7, f, 1);
    logger.setLink(8, f, 1);
    logger.setLink(10, t, 1); // inhibit high

    logger.setLink(9, f, 1);
    logger.simulate(0);
    logger.setLink(9, t, 1);
    logger.simulate(1);

    cr_assert(!fileExists("./log.bin"));
}

Test(chipset_logger, undefined_bit_skips_write)
{
    std::remove("./log.bin");

    nts::Logger logger;
    nts::TrueComponent t;
    nts::FalseComponent f;
    nts::UndefinedComponent u;

    logger.setLink(1, u, 1); // explicit undefined
    logger.setLink(2, f, 1);
    logger.setLink(3, f, 1);
    logger.setLink(4, f, 1);
    logger.setLink(5, f, 1);
    logger.setLink(6, f, 1);
    logger.setLink(7, f, 1);
    logger.setLink(8, f, 1);
    logger.setLink(10, f, 1); // inhibit low

    logger.setLink(9, f, 1);
    logger.simulate(0);
    logger.setLink(9, t, 1);
    logger.simulate(1);

    cr_assert(!fileExists("./log.bin"));
}
