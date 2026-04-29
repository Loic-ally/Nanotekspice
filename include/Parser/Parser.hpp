/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Parser.hpp
*/

#pragma once

#include "Circuit/Circuit.hpp"
#include "Components/Factory/ChipsetFactory.hpp"
#include "Parser/Lexer.hpp"
#include <set>
#include <string>
#include <vector>

namespace nts {
struct LinkRef {
    std::string leftName;
    std::size_t leftPin;
    std::string rightName;
    std::size_t rightPin;
    std::size_t line;
};

class Parser {
  public:
    Parser() = default;
    ~Parser() = default;
    nts::Circuit parseFile(const std::string &filepath);

  private:
    ChipsetFactory _factory;
    void handleChipsets(nts::Circuit &circuit,
                        const std::vector<nts::Token> &tokens);
    void handleLinks(nts::Circuit &circuit,
                     const std::vector<nts::Token> &tokens);
    std::size_t expectSection(const std::vector<Token> &tokens,
                              TokenType section, std::size_t pos) const;
    std::size_t parseChipsetLine(const std::vector<Token> &tokens,
                                 std::size_t pos, nts::Circuit &circuit,
                                 std::set<std::string> &definedNames);
    std::size_t parseLinkLine(const std::vector<Token> &tokens, std::size_t pos,
                              std::vector<LinkRef> &links);
    void validateLinks(nts::Circuit &circuit, const std::vector<LinkRef> &links,
                       const std::set<std::string> &definedNames) const;
    void ensureUniqueName(const nts::Circuit &circuit, const std::string &name,
                          std::size_t line) const;
};
} // namespace nts
