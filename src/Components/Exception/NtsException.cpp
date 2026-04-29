/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Custom exception hierarchy for NanoTekSpice
*/

#include "Components/Exception/NtsException.hpp"

namespace nts
{
    /**
     * @brief Construct a new Nts Exception:: Nts Exception object
     * 
     * @param message 
     */
    NtsException::NtsException(std::string message)
        : _message(std::move(message))
    {
    }

    /**
     * @brief Returns the explanatory string
     * 
     * @return const char* 
     */
    const char *NtsException::what() const noexcept
    {
        return _message.c_str();
    }

    /**
     * @brief Construct a new Lexical Or Syntax Error:: Lexical Or Syntax Error object
     * 
     * @param details 
     */
    LexicalOrSyntaxError::LexicalOrSyntaxError(const std::string &details)
        : NtsException("Lexical or syntax error: " + details)
    {
    }

    /**
     * @brief Construct a new Unknown Component Type Error:: Unknown Component Type Error object
     * 
     * @param type 
     */
    UnknownComponentTypeError::UnknownComponentTypeError(const std::string &type)
        : NtsException("Unknown component type: " + type)
    {
    }

    /**
     * @brief Construct a new Unknown Component Name Error:: Unknown Component Name Error object
     * 
     * @param name 
     */
    UnknownComponentNameError::UnknownComponentNameError(const std::string &name)
        : NtsException("Unknown component name: " + name)
    {
    }

    /**
     * @brief Construct a new Duplicate Component Name Error:: Duplicate Component Name Error object
     * 
     * @param name 
     */
    DuplicateComponentNameError::DuplicateComponentNameError(const std::string &name)
        : NtsException("Duplicate component name: " + name)
    {
    }

    /**
     * @brief Construct a new Missing Chipset Error:: Missing Chipset Error object
     * 
     */
    MissingChipsetError::MissingChipsetError()
        : NtsException("No chipsets declared in the circuit")
    {
    }

    /**
     * @brief Construct a new Invalid Pin Error:: Invalid Pin Error object
     * 
     * @param details 
     */
    InvalidPinError::InvalidPinError(const std::string &details)
        : NtsException("Invalid pin: " + details)
    {
    }

    /**
     * @brief Construct a new Parse Error:: Parse Error object
     * 
     * @param details 
     */
    ParseError::ParseError(const std::string &details)
        : NtsException("Parse error: " + details)
    {
    }
}
