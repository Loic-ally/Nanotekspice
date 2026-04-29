/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Token.hpp
*/

#pragma once

#include <cstddef>
#include <string>

namespace nts
{
    enum class TokenType {
        Chipsets,
        Links,
        Identifier,
        Number,
        Colon,
        Endline,
        EndOfFile,
        Invalid
    };

    struct Token
    {
        TokenType type;
        std::string lexeme;
        std::size_t line;
        std::size_t column;
    };
}
