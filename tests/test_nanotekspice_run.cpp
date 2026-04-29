#include <criterion/criterion.h>

#include "Nanotekspice.hpp"
#include "Components/Tristate/True.hpp"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <unistd.h>

namespace {
std::string writeTempNts(const std::string &content)
{
    std::ostringstream path;
    path << "/tmp/nanotekspice_run_" << getpid() << "_" << rand() << ".nts";
    std::string filename = path.str();

    std::ofstream out(filename);
    cr_assert(out.is_open(), "failed to create temp file: %s", filename.c_str());
    out << content;
    return filename;
}

void runApp(const std::string &path, const std::string &input,
            std::string &out, std::string &err)
{
    nts::Nanotekspice app(path);
    std::istringstream inputStream(input);
    std::ostringstream outputStream;
    std::ostringstream errorStream;

    auto *oldIn = std::cin.rdbuf(inputStream.rdbuf());
    auto *oldOut = std::cout.rdbuf(outputStream.rdbuf());
    auto *oldErr = std::cerr.rdbuf(errorStream.rdbuf());

    app.run();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);
    std::cerr.rdbuf(oldErr);

    out = outputStream.str();
    err = errorStream.str();
}
} // namespace

Test(nanotekspice_run, display_and_exit)
{
    const std::string content =
        ".chipsets:\n"
        "input in\n"
        "output out\n"
        ".links:\n"
        "in:1 out:1\n";

    std::string path = writeTempNts(content);
    std::string out;
    std::string err;

    runApp(path, "display\nexit\n", out, err);

    std::remove(path.c_str());

    cr_assert(out.find("tick: 0") != std::string::npos);
    cr_assert(out.find("input(s):") != std::string::npos);
    cr_assert(out.find("output(s):") != std::string::npos);
    cr_assert(err.empty());
}

Test(nanotekspice_run, simulate_then_display)
{
    const std::string content =
        ".chipsets:\n"
        "input in\n"
        "output out\n"
        ".links:\n"
        "in:1 out:1\n";

    std::string path = writeTempNts(content);
    std::string out;
    std::string err;

    runApp(path, "simulate\ndisplay\nexit\n", out, err);

    std::remove(path.c_str());

    cr_assert(out.find("tick: 1") != std::string::npos);
    cr_assert(err.empty());
}

Test(nanotekspice_run, help_command)
{
    const std::string content =
        ".chipsets:\n"
        "input in\n"
        "output out\n"
        ".links:\n"
        "in:1 out:1\n";

    std::string path = writeTempNts(content);
    std::string out;
    std::string err;

    runApp(path, "help\nexit\n", out, err);

    std::remove(path.c_str());

    cr_assert(out.find("Available commands:") != std::string::npos);
    cr_assert(err.empty());
}

Test(nanotekspice_run, set_value_then_display)
{
    const std::string content =
        ".chipsets:\n"
        "input in\n"
        "output out\n"
        ".links:\n"
        "in:1 out:1\n";

    std::string path = writeTempNts(content);
    std::string out;
    std::string err;

    runApp(path, "in=1\nsimulate\ndisplay\nexit\n", out, err);

    std::remove(path.c_str());

    cr_assert(out.find("in: 1") != std::string::npos);
    cr_assert(err.empty());
}

Test(nanotekspice_run, invalid_assignment_reports_error)
{
    const std::string content =
        ".chipsets:\n"
        "input in\n"
        "output out\n"
        ".links:\n"
        "in:1 out:1\n";

    std::string path = writeTempNts(content);
    std::string out;
    std::string err;

    runApp(path, "in=2\nexit\n", out, err);

    std::remove(path.c_str());

    cr_assert(err.find("Invalid value in assignment") != std::string::npos);
}

Test(nanotekspice_run, unknown_command_reports_error)
{
    const std::string content =
        ".chipsets:\n"
        "input in\n"
        "output out\n"
        ".links:\n"
        "in:1 out:1\n";

    std::string path = writeTempNts(content);
    std::string out;
    std::string err;

    runApp(path, "foobar\nexit\n", out, err);

    std::remove(path.c_str());

    cr_assert(err.find("Unknown command: foobar") != std::string::npos);
}

Test(nanotekspice_run, assignment_to_non_input_reports_error)
{
    const std::string content =
        ".chipsets:\n"
        "input in\n"
        "output out\n"
        ".links:\n"
        "in:1 out:1\n";

    std::string path = writeTempNts(content);
    std::string out;
    std::string err;

    runApp(path, "out=1\nexit\n", out, err);

    std::remove(path.c_str());

    cr_assert(err.find("Cannot set value on non-input component") != std::string::npos);
}
