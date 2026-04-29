#include <criterion/criterion.h>

#include "Components/Chipset/Logger.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/True.hpp"
#include <cstdio>
#include <fstream>

Test(chipset_logger, writes_on_rising_edge)
{
    std::remove("./log.bin");

    nts::Logger logger;
    nts::TrueComponent t;
    nts::FalseComponent f;

    // bits 1..8 -> 0b10101010
    logger.setLink(1, f, 1);
    logger.setLink(2, t, 1);
    logger.setLink(3, f, 1);
    logger.setLink(4, t, 1);
    logger.setLink(5, f, 1);
    logger.setLink(6, t, 1);
    logger.setLink(7, f, 1);
    logger.setLink(8, t, 1);
    logger.setLink(10, f, 1); // inhibit low

    logger.setLink(9, f, 1); // clock low
    logger.simulate(0);

    logger.setLink(9, t, 1); // rising edge
    logger.simulate(1);

    std::ifstream in("./log.bin", std::ios::binary);
    cr_assert(in.is_open());
    char byte = 0;
    in.read(&byte, 1);
    cr_assert_eq(static_cast<unsigned char>(byte), 0xAA);

    std::remove("./log.bin");
}
