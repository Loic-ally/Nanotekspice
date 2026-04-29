#include <criterion/criterion.h>

#include "Parser/Lexer.hpp"
#include "Parser/Parser.hpp"
#include "Components/Exception/NtsException.hpp"
#include "Components/Tristate/True.hpp"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>

static std::string writeTempNts(const std::string &content)
{
    std::ostringstream path;
    path << "/tmp/nanotekspice_test_" << getpid() << "_" << rand() << ".nts";
    std::string filename = path.str();

    std::ofstream out(filename);
    cr_assert(out.is_open(), "failed to create temp file: %s", filename.c_str());
    out << content;
    return filename;
}

Test(lexer, recognizes_sections_and_identifiers)
{
    const std::string input =
        ".chipsets:\n"
        "# comment\n"
        "input in\n"
        ".links:\n"
        "in:1 out:1\n";

    nts::Lexer lexer(input);
    auto tokens = lexer.tokenize();

    cr_assert(tokens.size() > 6);
    cr_assert_eq(tokens[0].type, nts::TokenType::Chipsets);
    cr_assert_eq(tokens[1].type, nts::TokenType::Endline);
    cr_assert_eq(tokens[2].type, nts::TokenType::Endline);
    cr_assert_eq(tokens[3].type, nts::TokenType::Identifier);
    cr_assert_eq(tokens[4].type, nts::TokenType::Identifier);
}

Test(lexer, invalid_char_emits_invalid_token)
{
    nts::Lexer lexer("@");
    auto tokens = lexer.tokenize();

    cr_assert_eq(tokens[0].type, nts::TokenType::Invalid);
    cr_assert_eq(tokens[0].line, 1);
    cr_assert_eq(tokens[0].column, 1);
}

Test(parser, parse_valid_file_builds_circuit)
{
    const std::string content =
        ".chipsets:\n"
        "input in\n"
        "output out\n"
        "and gate\n"
        ".links:\n"
        "in:1 gate:1\n"
        "in:1 gate:2\n"
        "gate:3 out:1\n";

    std::string path = writeTempNts(content);

    nts::Parser parser;
    nts::Circuit circuit = parser.parseFile(path);

    std::remove(path.c_str());

    cr_assert(circuit.hasComponent("in"));
    cr_assert(circuit.hasComponent("out"));
    cr_assert(circuit.hasComponent("gate"));
    cr_assert_eq(circuit.getInputs().size(), 1);
    cr_assert_eq(circuit.getOutputs().size(), 1);

    nts::TrueComponent t;
    circuit.getComponent("in").setLink(1, t, 1);
    circuit.simulate(1);
    cr_assert_eq(circuit.computeComponent("out", 1), nts::True);
}

Test(parser, wrong_extension_rejected)
{
    nts::Parser parser;
    cr_assert_throw(parser.parseFile("/tmp/not_a_circuit.txt"), nts::ParseError);
}

Test(parser, unknown_component_type_throws)
{
    const std::string content =
        ".chipsets:\n"
        "unknown_type foo\n"
        ".links:\n";

    std::string path = writeTempNts(content);
    nts::Parser parser;

    cr_assert_throw(parser.parseFile(path), nts::UnknownComponentTypeError);

    std::remove(path.c_str());
}
