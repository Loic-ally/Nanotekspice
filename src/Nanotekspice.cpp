/*
** EPITECH PROJECT, 2025
** G-OOP-400-MLH-4-1-tekspice-6
** File description:
** Nanotekspice.cpp
*/

#include "Nanotekspice.hpp"
#include "Components/Exception/NtsException.hpp"
#include "Components/Tristate/True.hpp"
#include "Components/Tristate/False.hpp"
#include "Components/Tristate/Undefined.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>

namespace nts
{

    /**
     * @brief Overloads the stream insertion operator for Tristate values
     * 
     * @param os The output stream
     * @param value The Tristate value to be printed
     * @return std::ostream& The output stream with the Tristate value inserted
     */
    std::ostream &operator<<(std::ostream &os, Tristate value)
    {
        switch (value) {
        case True:
            return os << '1';
        case False:
            return os << '0';
        default:
            return os << 'U';
        }
    }
    /**
     * @brief Construct a new Nanotekspice:: Nanotekspice object
     * 
     * @param filepath 
     */
    Nanotekspice::Nanotekspice(const std::string &filepath)
        : _circuit(_parser.parseFile(filepath))
    {
    }

    /**
     * @brief Runs the main loop of the Nanotekspice application
     * 
     * @return int 
     */
    int Nanotekspice::run()
    {
        bool running = true;
        bool looping = false;

        while (running) {
            if (!looping)
                std::cout << "> " << std::flush;
            std::string line;
            if (!std::getline(std::cin, line))
                break;
            if (looping && line == "") {
                continue;
            }
            try {
                handleCommand(line, running, looping);
            } catch (const nts::NtsException &e) {
                std::cerr << e.what() << std::endl;
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
        return 0;
    }

    /**
     * @brief Handles a command entered by the user
     * 
     * @param line The command line entered by the user
     * @param running A reference to the running state of the application
     * @param looping A reference to the looping state of the application
     */
    void Nanotekspice::handleCommand(const std::string &line, bool &running, bool &looping)
    {
        if (line == "exit") {
            running = false;
            return;
        }
        if (line == "display") {
            commandDisplay();
            return;
        }
        if (line == "simulate") {
            commandSimulate();
            return;
        }
        if (line == "loop") {
            toggleLoop(looping);
            return;
        }
        if (line.find('=') != std::string::npos) {
            commandSetValue(line);
            return;
        }
        if (line == "help") {
            std::cout << "Available commands:" << std::endl;
            std::cout << "  display           - Display the current state of the circuit" << std::endl;
            std::cout << "  simulate          - Simulate the circuit for one tick" << std::endl;
            std::cout << "  loop              - Continuously simulate and display until interrupted" << std::endl;
            std::cout << "  <name>=<value>   - Set the value of a component (1, 0, U)" << std::endl;
            std::cout << "  exit              - Exit the application" << std::endl;
            return;
        }
        std::cerr << "Unknown command: " << line << std::endl;
    }

    /**
     * @brief Simulates the circuit for one tick
     * 
     */
    void Nanotekspice::commandSimulate()
    {
        ++_tick;
        _circuit.simulate(_tick);
    }

    /**
     * @brief Displays the current state of the circuit, including inputs and outputs
     * 
     */
    void Nanotekspice::commandDisplay()
    {
        std::cout << "tick: " << _tick << std::endl;
        std::vector<std::string> inputs;
        std::vector<std::string> outputs;
        const auto &inputPtrs = _circuit.getInputs();
        const auto &clockPtrs = _circuit.getClocks();
        const auto &outputPtrs = _circuit.getOutputs();
        for (const auto &kv : _circuit.getComponents()) {
            IComponent *ptr = kv.second.get();
            if (std::find(inputPtrs.begin(), inputPtrs.end(), ptr) != inputPtrs.end() ||
                std::find(clockPtrs.begin(), clockPtrs.end(), ptr) != clockPtrs.end()) {
                inputs.push_back(kv.first);
            } else if (std::find(outputPtrs.begin(), outputPtrs.end(), ptr) != outputPtrs.end()) {
                outputs.push_back(kv.first);
            }
        }
        std::sort(inputs.begin(), inputs.end());
        std::sort(outputs.begin(), outputs.end());
        std::cout << "input(s):" << std::endl;
        for (const auto &name : inputs) {
            auto &comp = _circuit.getComponent(name);
            Tristate v = comp.compute(1);
            std::cout << "  " << name << ": " << v << std::endl;
        }
        std::cout << "output(s):" << std::endl;
        for (const auto &name : outputs) {
            auto &comp = _circuit.getComponent(name);
            Tristate v = comp.compute(1);
            std::cout << "  " << name << ": " << v << std::endl;
        }
    }

    /**
     * @brief Sets the value of a component based on an assignment string
     * 
     * @param assignment The assignment string in the format "name=value"
     */
    void Nanotekspice::commandSetValue(const std::string &assignment)
    {
        auto pos = assignment.find('=');
        if (pos == std::string::npos)
            throw ParseError("Invalid assignment: " + assignment);
        std::string name = assignment.substr(0, pos);
        std::string valStr = assignment.substr(pos + 1);
        Tristate value = Undefined;
        if (valStr == "1")
            value = True;
        else if (valStr == "0")
            value = False;
        else if (valStr == "U" || valStr == "u")
            value = Undefined;
        else
            throw ParseError("Invalid value in assignment: " + assignment);
        if (!_circuit.hasComponent(name))
            throw UnknownComponentNameError(name);
        IComponent &comp = _circuit.getComponent(name);
        const auto &inputPtrs = _circuit.getInputs();
        const auto &clockPtrs = _circuit.getClocks();
        IComponent *ptr = &comp;
        if (std::find(inputPtrs.begin(), inputPtrs.end(), ptr) == inputPtrs.end() &&
            std::find(clockPtrs.begin(), clockPtrs.end(), ptr) == clockPtrs.end())
            throw ParseError("Cannot set value on non-input component: " + name);
        TrueComponent trueComp;
        FalseComponent falseComp;
        UndefinedComponent undefComp;
        if (value == True)
            comp.setLink(1, trueComp, 1);
        else if (value == False)
            comp.setLink(1, falseComp, 1);
        else
            comp.setLink(1, undefComp, 1);
    }

    /**
     * @brief Toggles the simulation loop on or off
     * 
     * @param looping A reference to a boolean indicating whether the loop is active
     */
    void Nanotekspice::toggleLoop(bool &looping)
    {
        looping = true;
        _signalHandler.setup();
        while (!_signalHandler.isInterrupted()) {
            commandSimulate();
            commandDisplay();
        }
        _signalHandler.reset();
        looping = false;
    }

}
