/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** ParsingContext.hpp
*/

#pragma once

#include "Parser/Token.hpp"
#include <cstddef>
#include <vector>

namespace nts
{
    struct ParsingContext
    {
        std::vector<Token> tokens;
        std::size_t index = 0;
    };
}
