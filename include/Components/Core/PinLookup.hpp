/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Pin index lookup helper declarations
*/

#pragma once

#include <cstddef>
#include <span>

namespace nts {
int pinIndex(std::size_t pin, std::span<const std::size_t> pins);
} // namespace nts
