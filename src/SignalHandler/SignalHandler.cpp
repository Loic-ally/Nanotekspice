/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** SignalHandler.cpp
*/

#include "SignalHandler/SignalHandler.hpp"

namespace nts
{
    volatile sig_atomic_t SignalHandler::_interrupted = 0;

    /**
     * @brief Signal handler for interrupt signals
     * 
     * @param signum The signal number
     */
    void SignalHandler::handler(int)
    {
        _interrupted = 1;
    }

    /**
     * @brief Sets up the signal handler for interrupt signals
     * 
     */
    void SignalHandler::setup()
    {
        _interrupted = 0;
        struct sigaction sa = {};
        sa.sa_handler = handler;
        sigaction(SIGINT, &sa, nullptr);
    }

    /**
     * @brief Resets the interrupted state to allow for a new simulation loop
     * 
     */
    void SignalHandler::reset()
    {
        _interrupted = 0;
    }

    /**
     * @brief Checks if the simulation loop has been interrupted
     * 
     * @return true If the simulation loop has been interrupted
     * @return false If the simulation loop has not been interrupted
     */
    bool SignalHandler::isInterrupted() const
    {
        return _interrupted != 0;
    }
}
