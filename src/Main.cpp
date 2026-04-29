/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** main.cpp
*/

#include "Nanotekspice.hpp"
#include "Components/Exception/NtsException.hpp"
#include <iostream>
#include <string>

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <circuit_file>" << std::endl;
        return 84;
    }
    try {
        nts::Nanotekspice app(av[1]);
        app.run();
    } catch (const nts::NtsException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
