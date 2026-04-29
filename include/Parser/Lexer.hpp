/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Lexer.hpp
*/

#pragma once

#include "Parser/Token.hpp"
#include <string>
#include <vector>

namespace nts {
class Lexer {
  public:
    explicit Lexer(const std::string &input);
    ~Lexer() = default;
    std::vector<Token> tokenize();

  private:
    const std::string _input;
    std::size_t _pos = 0;
    std::size_t _line = 1;
    std::size_t _col = 1;

    char peek() const;
    char get();
    void skipSpaces();
    void skipComment();
    Token makeIdentifier();
    Token makeNumber();
};
} // namespace nts
