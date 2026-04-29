#include <criterion/criterion.h>

#include "SignalHandler/SignalHandler.hpp"
#include <csignal>

Test(signal_handler, interrupt_and_reset)
{
    nts::SignalHandler handler;

    handler.setup();
    raise(SIGINT);
    cr_assert(handler.isInterrupted());

    handler.reset();
    cr_assert(!handler.isInterrupted());
}
