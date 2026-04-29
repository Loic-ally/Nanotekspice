/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Parser.cpp
*/

#include "Parser/Parser.hpp"
#include "Components/Exception/NtsException.hpp"
#include <fstream>
#include <set>
#include <sstream>

namespace nts {
/**
 * @brief Parses a .nts file and returns a Circuit object
 *
 * @param filepath The path to the .nts file
 * @return nts::Circuit The parsed circuit
 * @throws ParseError if the file cannot be read or if the syntax is invalid
 * @throws MissingChipsetError if no chipsets are defined in the file
 */
nts::Circuit Parser::parseFile(const std::string &filepath) {
    if (filepath.length() < 5 ||
        filepath.substr(filepath.length() - 4) != ".nts")
        throw ParseError("File must have .nts extension");
    std::ifstream file(filepath);
    if (!file)
        throw ParseError("Cannot open file: " + filepath);
    std::ostringstream oss;
    oss << file.rdbuf();
    std::string content = oss.str();
    Lexer lexer(content);
    std::vector<Token> tokens = lexer.tokenize();
    for (const auto &t : tokens) {
        if (t.type == TokenType::Invalid)
            throw ParseError("Invalid token '" + t.lexeme + "' at line " +
                             std::to_string(t.line));
    }
    Circuit circuit;
    std::size_t pos = 0;
    bool hasChipset = false;
    std::set<std::string> definedNames;

    while (pos < tokens.size() && tokens[pos].type == TokenType::Endline)
        pos++;
    pos = expectSection(tokens, TokenType::Chipsets, pos) + 1;
    if (pos < tokens.size() && tokens[pos].type == TokenType::Endline)
        pos++;
    while (pos < tokens.size() && tokens[pos].type == TokenType::Endline)
        pos++;
    while (pos < tokens.size() && tokens[pos].type != TokenType::Links) {
        if (tokens[pos].type == TokenType::EndOfFile)
            throw ParseError("Missing .links: section");
        if (tokens[pos].type == TokenType::Endline) {
            pos++;
            continue;
        }
        pos = parseChipsetLine(tokens, pos, circuit, definedNames);
        hasChipset = true;
    }
    if (!hasChipset)
        throw MissingChipsetError();
    pos = expectSection(tokens, TokenType::Links, pos) + 1;
    if (pos < tokens.size() && tokens[pos].type == TokenType::Endline)
        pos++;
    std::vector<LinkRef> links;
    while (pos < tokens.size() && tokens[pos].type != TokenType::EndOfFile) {
        if (tokens[pos].type == TokenType::Endline) {
            pos++;
            continue;
        }
        pos = parseLinkLine(tokens, pos, links);
    }
    validateLinks(circuit, links, definedNames);
    return circuit;
}

/**
 * @brief Checks if the current token matches the expected section token
 *
 * @param tokens The list of tokens
 * @param section The expected section token type
 * @param pos The current position in the token list
 * @return std::size_t The position of the section token
 * @throws ParseError if the expected section token is not found
 */
std::size_t Parser::expectSection(const std::vector<Token> &tokens,
                                  TokenType section, std::size_t pos) const {
    if (pos >= tokens.size() || tokens[pos].type != section)
        throw ParseError("Expected section token");
    return pos;
}

/**
 * @brief Parses a chipset line and adds the component to the circuit
 *
 * @param tokens The list of tokens
 * @param pos The current position in the token list
 * @param circuit The circuit being constructed
 * @param definedNames The set of already defined component names
 * @return std::size_t The new position in the token list after parsing the line
 * @throws ParseError if the chipset line is malformed
 */
std::size_t Parser::parseChipsetLine(const std::vector<Token> &tokens,
                                     std::size_t pos, nts::Circuit &circuit,
                                     std::set<std::string> &definedNames) {
    if (pos + 1 >= tokens.size())
        throw ParseError("Incomplete chipset line");
    bool typeOk = (tokens[pos].type == TokenType::Identifier ||
                   tokens[pos].type == TokenType::Number);
    if (!typeOk || tokens[pos + 1].type != TokenType::Identifier)
        throw ParseError("Invalid chipset line");
    std::string type = tokens[pos].lexeme;
    std::string name = tokens[pos + 1].lexeme;
    if (definedNames.count(name))
        throw DuplicateComponentNameError(name);
    definedNames.insert(name);
    ensureUniqueName(circuit, name, tokens[pos].line);
    if (!_factory.has(type))
        throw UnknownComponentTypeError(type);
    std::unique_ptr<IComponent> comp = _factory.createComponent(type);
    circuit.addComponent(name, std::move(comp));
    if (type == "input")
        circuit.addInput(name);
    else if (type == "output")
        circuit.addOutput(name);
    else if (type == "clock")
        circuit.addClock(name);
    pos += 2;
    if (pos < tokens.size() && tokens[pos].type == TokenType::Endline)
        pos++;
    else
        throw ParseError("Chipset line must end with newline");
    return pos;
}

/**
 * @brief Parses a link line and adds the link reference to the list
 *
 * @param tokens The list of tokens
 * @param pos The current position in the token list
 * @param links The list of link references being constructed
 * @return std::size_t The new position in the token list after parsing the line
 * @throws ParseError if the link line is malformed
 */
std::size_t Parser::parseLinkLine(const std::vector<Token> &tokens,
                                  std::size_t pos,
                                  std::vector<LinkRef> &links) {
    auto expect = [&](TokenType t, const std::string &msg) {
        if (pos >= tokens.size() || tokens[pos].type != t)
            throw ParseError(msg);
    };
    expect(TokenType::Identifier, "Link line: expected component name");
    std::string leftName = tokens[pos].lexeme;
    std::size_t line = tokens[pos].line;
    pos++;
    expect(TokenType::Colon, "Link line: expected ':' after left name");
    pos++;
    expect(TokenType::Number, "Link line: expected pin number after ':'");
    std::size_t leftPin = std::stoul(tokens[pos].lexeme);
    pos++;
    expect(TokenType::Identifier, "Link line: expected right component name");
    std::string rightName = tokens[pos].lexeme;
    pos++;
    expect(TokenType::Colon, "Link line: expected ':' after right name");
    pos++;
    expect(TokenType::Number, "Link line: expected pin number after ':'");
    std::size_t rightPin = std::stoul(tokens[pos].lexeme);
    pos++;
    if (pos < tokens.size() && tokens[pos].type == TokenType::Endline)
        pos++;
    else
        throw ParseError("Link line must end with newline");
    links.push_back(LinkRef{leftName, leftPin, rightName, rightPin, line});
    return pos;
}

/**
 * @brief Validates the links between components in the circuit
 *
 * @param circuit The circuit containing the components
 * @param links The list of link references
 * @param definedNames The set of already defined component names
 * @throws UnknownComponentNameError if a link references an undefined component
 */
void Parser::validateLinks(nts::Circuit &circuit,
                           const std::vector<LinkRef> &links,
                           const std::set<std::string> &definedNames) const {
    for (const auto &l : links) {
        if (definedNames.find(l.leftName) == definedNames.end())
            throw UnknownComponentNameError(l.leftName);
        if (definedNames.find(l.rightName) == definedNames.end())
            throw UnknownComponentNameError(l.rightName);
    }
    for (const auto &l : links) {
        nts::IComponent &left = circuit.getComponent(l.leftName);
        nts::IComponent &right = circuit.getComponent(l.rightName);
        left.setLink(l.leftPin, right, l.rightPin);
    }
}

/**
 * @brief Ensures that the component name is unique within the circuit
 *
 * @param circuit The circuit containing the components
 * @param name The name to check for uniqueness
 */
void Parser::ensureUniqueName(const nts::Circuit &circuit,
                              const std::string &name, std::size_t) const {
    if (circuit.hasComponent(name))
        throw DuplicateComponentNameError(name);
}
} // namespace nts
