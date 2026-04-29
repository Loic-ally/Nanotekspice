/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Custom exception hierarchy for NanoTekSpice
*/

#pragma once

#include <exception>
#include <string>

namespace nts
{
    class NtsException : public std::exception
    {
    public:
        explicit NtsException(std::string message);
        ~NtsException() override = default;
        const char *what() const noexcept override;

    protected:
        std::string _message;
    };

    class LexicalOrSyntaxError : public NtsException
    {
    public:
        explicit LexicalOrSyntaxError(const std::string &details);
    };

    class UnknownComponentTypeError : public NtsException
    {
    public:
        explicit UnknownComponentTypeError(const std::string &type);
    };

    class UnknownComponentNameError : public NtsException
    {
    public:
        explicit UnknownComponentNameError(const std::string &name);
    };

    class DuplicateComponentNameError : public NtsException
    {
    public:
        explicit DuplicateComponentNameError(const std::string &name);
    };

    class MissingChipsetError : public NtsException
    {
    public:
        MissingChipsetError();
    };

    class InvalidPinError : public NtsException
    {
    public:
        explicit InvalidPinError(const std::string &details);
    };

    class ParseError : public NtsException
    {
    public:
        explicit ParseError(const std::string &details);
    };
}
