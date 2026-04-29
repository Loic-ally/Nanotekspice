#include "Components/Chipset/C4040.hpp"
#include "Components/Chipset/C4013.hpp"
#include "Components/Core/AComponent.hpp"
#include "Components/Core/IComponent.hpp"
#include "Components/Operators/NotGate.hpp"
#include "Components/Tristate/False.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>

namespace nts {

/**
 * @brief Construct a new 4040::4040 object
 *
 */
C4040::C4040() : AComponent("C4040", 14, {8, 16}) {

    for (auto &flipflop : _flipflopList) {
        flipflop = std::make_unique<C4013>();
    }
    _false = std::make_unique<FalseComponent>();
    _not = std::make_unique<NotGate>();

    _not->setLink(1, *this, 10, false);
    _flipflopList[0]->setLink(3, *_not, 2, false);

    _flipflopList[0]->setLink(6, *_false, 1, false);
    _flipflopList[0]->setLink(8, *_false, 1, false);
    _flipflopList[0]->setLink(4, *this, 11, false);
    _flipflopList[0]->setLink(10, *this, 11, false);
    _flipflopList[0]->setLink(5, *_flipflopList[0], 2, false);
    _flipflopList[0]->setLink(11, *_flipflopList[0], 2, false);
    _flipflopList[0]->setLink(9, *_flipflopList[0], 12, false);

    _flipflopList[1]->setLink(3, *_flipflopList[0], 12, false);

    _flipflopList[1]->setLink(6, *_false, 1);
    _flipflopList[1]->setLink(8, *_false, 1, false);
    _flipflopList[1]->setLink(4, *this, 11, false);
    _flipflopList[1]->setLink(10, *this, 11, false);
    _flipflopList[1]->setLink(5, *_flipflopList[1], 2, false);
    _flipflopList[1]->setLink(11, *_flipflopList[1], 2, false);
    _flipflopList[1]->setLink(9, *_flipflopList[1], 12, false);

    _flipflopList[2]->setLink(3, *_flipflopList[1], 12, false);

    _flipflopList[2]->setLink(6, *_false, 1, false);
    _flipflopList[2]->setLink(8, *_false, 1, false);
    _flipflopList[2]->setLink(4, *this, 11, false);
    _flipflopList[2]->setLink(10, *this, 11, false);
    _flipflopList[2]->setLink(5, *_flipflopList[2], 2, false);
    _flipflopList[2]->setLink(11, *_flipflopList[2], 2, false);
    _flipflopList[2]->setLink(9, *_flipflopList[2], 12, false);

    _flipflopList[3]->setLink(3, *_flipflopList[2], 12, false);

    _flipflopList[3]->setLink(6, *_false, 1, false);
    _flipflopList[3]->setLink(8, *_false, 1, false);
    _flipflopList[3]->setLink(4, *this, 11, false);
    _flipflopList[3]->setLink(10, *this, 11, false);
    _flipflopList[3]->setLink(5, *_flipflopList[3], 2, false);
    _flipflopList[3]->setLink(11, *_flipflopList[3], 2, false);
    _flipflopList[3]->setLink(9, *_flipflopList[3], 12, false);

    _flipflopList[4]->setLink(3, *_flipflopList[3], 12, false);

    _flipflopList[4]->setLink(6, *_false, 1, false);
    _flipflopList[4]->setLink(8, *_false, 1, false);
    _flipflopList[4]->setLink(4, *this, 11, false);
    _flipflopList[4]->setLink(10, *this, 11, false);
    _flipflopList[4]->setLink(5, *_flipflopList[4], 2, false);
    _flipflopList[4]->setLink(11, *_flipflopList[4], 2, false);
    _flipflopList[4]->setLink(9, *_flipflopList[4], 12, false);

    _flipflopList[5]->setLink(3, *_flipflopList[4], 12, false);

    _flipflopList[5]->setLink(6, *_false, 1, false);
    _flipflopList[5]->setLink(8, *_false, 1, false);
    _flipflopList[5]->setLink(4, *this, 11, false);
    _flipflopList[5]->setLink(10, *this, 11, false);
    _flipflopList[5]->setLink(5, *_flipflopList[5], 2, false);
    _flipflopList[5]->setLink(11, *_flipflopList[5], 2, false);
    _flipflopList[5]->setLink(9, *_flipflopList[5], 12, false);
};

void C4040::simulate(std::size_t tick) {
    _flipflopList[0]->simulate(tick);
    _flipflopList[1]->simulate(tick);
    _flipflopList[2]->simulate(tick);
    _flipflopList[3]->simulate(tick);
    _flipflopList[4]->simulate(tick);
    _flipflopList[5]->simulate(tick);
    _false->simulate(tick);
}

/**
 * @brief Compute the output of the C4040 component for a given pin
 *
 * @param pin The pin number to compute
 * @return Tristate The computed value of the pin
 */
Tristate C4040::compute(std::size_t pin) {
    switch (pin) {
    case 9:
        return _flipflopList[0]->compute(1);
    case 7:
        return _flipflopList[0]->compute(13);
    case 6:
        return _flipflopList[1]->compute(1);
    case 5:
        return _flipflopList[1]->compute(13);
    case 3:
        return _flipflopList[2]->compute(1);
    case 2:
        return _flipflopList[2]->compute(13);
    case 4:
        return _flipflopList[3]->compute(1);
    case 13:
        return _flipflopList[3]->compute(13);
    case 12:
        return _flipflopList[4]->compute(1);
    case 14:
        return _flipflopList[4]->compute(13);
    case 15:
        return _flipflopList[5]->compute(1);
    case 1:
        return _flipflopList[5]->compute(13);
    default:
        return getLink(pin);
    }
};

} // namespace nts