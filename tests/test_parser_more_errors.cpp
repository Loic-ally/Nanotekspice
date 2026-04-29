#include <criterion/criterion.h>

#include "Parser/Parser.hpp"
#include "Components/Exception/NtsException.hpp"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>

static std::string writeTempNts(const std::string &content)
{
    std::ostringstream path;
    path << "/tmp/nanotekspice_parse_" << getpid() << "_" << rand() << ".nts";
    std::string filename = path.str();

    std::ofstream out(filename);
    cr_assert(out.is_open(), "failed to create temp file: %s", filename.c_str());
    out << content;
    return filename;
}

Test(parser_errors, links_before_chipsets)
{
    const std::string content =
        ".links:\n"
        "in:1 out:1\n";

    std::string path = writeTempNts(content);
    nts::Parser parser;

    cr_assert_throw(parser.parseFile(path), nts::ParseError);

    std::remove(path.c_str());
}

Test(parser_errors, link_missing_colon)
{
    const std::string content =
        ".chipsets:\n"
        "input in\n"
        "output out\n"
        ".links:\n"
        "in 1 out:1\n";

    std::string path = writeTempNts(content);
    nts::Parser parser;

    cr_assert_throw(parser.parseFile(path), nts::ParseError);

    std::remove(path.c_str());
}

Test(parser_errors, link_missing_pin)
{
    const std::string content =
        ".chipsets:\n"
        "input in\n"
        "output out\n"
        ".links:\n"
        "in: out:1\n";

    std::string path = writeTempNts(content);
    nts::Parser parser;

    cr_assert_throw(parser.parseFile(path), nts::ParseError);

    std::remove(path.c_str());
}

Test(parser_errors, link_missing_newline_at_eof)
{
    const std::string content =
        ".chipsets:\n"
        "input in\n"
        "output out\n"
        ".links:\n"
        "in:1 out:1";

    std::string path = writeTempNts(content);
    nts::Parser parser;

    cr_assert_throw(parser.parseFile(path), nts::ParseError);

    std::remove(path.c_str());
}
