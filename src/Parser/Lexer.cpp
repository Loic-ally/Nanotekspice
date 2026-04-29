/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Lexer.cpp
*/

#include "Parser/Lexer.hpp"
#include <cctype>

namespace nts {
/**
 * @brief Construct a new Lexer:: Lexer object
 *
 * @param input
 */
Lexer::Lexer(const std::string &input) : _input(std::move(input)) {}

/**
 * @brief Returns the current character without advancing the position
 *
 * @return char The current character or '\0' if at the end of input
 */
char Lexer::peek() const {
    if (_pos >= _input.size())
        return '\0';
    return _input[_pos];
}

/**
 * @brief Returns the current character and advances the position
 *
 * @return char The current character or '\0' if at the end of input
 */
char Lexer::get() {
    if (_pos >= _input.size())
        return '\0';
    char c = _input[_pos++];
    if (c == '\n') {
        _line++;
        _col = 1;
    } else {
        _col++;
    }
    return c;
}

/**
 * @brief Skips whitespace characters except for newlines
 */
void Lexer::skipSpaces() {
    while (std::isspace(peek()) && peek() != '\n')
        get();
}

/**
 * @brief Skips comments starting with '#' until the end of the line
 */
void Lexer::skipComment() {
    if (peek() == '#') {
        while (peek() != '\n' && peek() != '\0')
            get();
    }
}

/**
 * @brief Parses an identifier token (alphanumeric or underscore)
 *
 * @return Token The parsed identifier token
 */
Token Lexer::makeIdentifier() {
    std::size_t startCol = _col;
    std::string lex;
    while (std::isalnum(peek()) || peek() == '_')
        lex.push_back(get());
    return Token{TokenType::Identifier, lex, _line, startCol};
}

/**
 * @brief Parses a number token (sequence of digits)
 *
 * @return Token The parsed number token
 */
Token Lexer::makeNumber() {
    std::size_t startCol = _col;
    std::string lex;
    while (std::isdigit(peek()))
        lex.push_back(get());
    return Token{TokenType::Number, lex, _line, startCol};
}

/**
 * @brief Tokenizes the input string into a list of tokens
 *
 * @return std::vector<Token> The list of tokens extracted from the input
 */
std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (true) {
        skipSpaces();
        skipComment();
        char c = peek();
        if (c == '\0') {
            tokens.push_back(Token{TokenType::EndOfFile, "", _line, _col});
            break;
        }
        if (c == '\n') {
            get();
            tokens.push_back(Token{TokenType::Endline, "\\n", _line - 1, _col});
            continue;
        }
        if (c == '.') {
            std::size_t startCol = _col;
            std::string rest = _input.substr(_pos);
            if (rest.rfind(".chipsets:", 0) == 0) {
                _pos += 10;
                _col += 10;
                tokens.push_back(
                    Token{TokenType::Chipsets, ".chipsets:", _line, startCol});
                continue;
            }
            if (rest.rfind(".links:", 0) == 0) {
                _pos += 7;
                _col += 7;
                tokens.push_back(
                    Token{TokenType::Links, ".links:", _line, startCol});
                continue;
            }
            tokens.push_back(Token{TokenType::Invalid, ".", _line, startCol});
            get();
            continue;
        }
        if (c == ':') {
            tokens.push_back(Token{TokenType::Colon, ":", _line, _col});
            get();
            continue;
        }
        if (std::isalpha(c) || c == '_') {
            tokens.push_back(makeIdentifier());
            continue;
        }
        if (std::isdigit(c)) {
            tokens.push_back(makeNumber());
            continue;
        }
        tokens.push_back(
            Token{TokenType::Invalid, std::string(1, c), _line, _col});
        get();
    }
    return tokens;
}
} // namespace nts