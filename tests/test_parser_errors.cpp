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
    path << "/tmp/nanotekspice_error_" << getpid() << "_" << rand() << ".nts";
    std::string filename = path.str();

    std::ofstream out(filename);
    cr_assert(out.is_open(), "failed to create temp file: %s", filename.c_str());
    out << content;
    return filename;
}

Test(parser_errors, missing_links_section)
{
    const std::string content =
        ".chipsets:\n"
        "input in\n";

    std::string path = writeTempNts(content);
    nts::Parser parser;

    cr_assert_throw(parser.parseFile(path), nts::ParseError);

    std::remove(path.c_str());
}

Test(parser_errors, missing_chipsets_section)
{
    const std::string content =
        ".chipsets:\n"
        ".links:\n";

    std::string path = writeTempNts(content);
    nts::Parser parser;

    cr_assert_throw(parser.parseFile(path), nts::MissingChipsetError);

    std::remove(path.c_str());
}

Test(parser_errors, duplicate_component_name)
{
    const std::string content =
        ".chipsets:\n"
        "input in\n"
        "input in\n"
        ".links:\n";

    std::string path = writeTempNts(content);
    nts::Parser parser;

    cr_assert_throw(parser.parseFile(path), nts::DuplicateComponentNameError);

    std::remove(path.c_str());
}

Test(parser_errors, unknown_component_in_links)
{
    const std::string content =
        ".chipsets:\n"
        "input in\n"
        "output out\n"
        ".links:\n"
        "in:1 missing:1\n";

    std::string path = writeTempNts(content);
    nts::Parser parser;

    cr_assert_throw(parser.parseFile(path), nts::UnknownComponentNameError);

    std::remove(path.c_str());
}

Test(parser_errors, invalid_chipset_line)
{
    const std::string content =
        ".chipsets:\n"
        "input\n"
        ".links:\n";

    std::string path = writeTempNts(content);
    nts::Parser parser;

    cr_assert_throw(parser.parseFile(path), nts::ParseError);

    std::remove(path.c_str());
}

Test(parser_errors, invalid_token_in_file)
{
    const std::string content = "@";

    std::string path = writeTempNts(content);
    nts::Parser parser;

    cr_assert_throw(parser.parseFile(path), nts::ParseError);

    std::remove(path.c_str());
}
