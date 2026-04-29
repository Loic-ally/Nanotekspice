#include "Components/Chipset/C4001.hpp"

namespace nts {

/**
 * @brief Construct a new C4001::C4001 object
 * 
 */
C4001::C4001() : QuadBinaryGateChipset<NorGate>("C4001") {}

/**
 * @brief Simulates the C4001 component for the given tick.
 * 
 * @param tick The current simulation tick.
 */
void C4001::simulate(std::size_t tick) {
    (void)tick;
    simulateQuad();
}
} // namespace nts
