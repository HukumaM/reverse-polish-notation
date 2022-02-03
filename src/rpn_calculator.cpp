/**
 * @file rpn_calculator.cpp
 * @author Nikita Mashtalirov (nik.mashtalirov@yandex.ru)
 * @brief Reverse polish notation (RPN)
 * @version 0.1
 * @date 2022-01-27
 * 
 * @copyright Copyright (c) 2022
 */

#include <iostream>

#include "rpn_calculator.hpp"

auto main([[maybe_unused]] int argc,
          [[maybe_unused]] char *argv[]) -> int
{
    std::cerr << "The end character of the input is ^D\n";
    std::vector<std::string> storage;
    storage.reserve(argc);
    std::cerr << ">> ";
    std::copy(std::istream_iterator<std::string>{std::cin},
              std::istream_iterator<std::string>{},
              std::back_inserter(storage));
    try
    {
        auto result = reverse_polish_notation::evaluate(std::cbegin(storage),
                                                        std::cend(storage));
        std::cout << "<< " << result << std::endl;
    }
    catch (std::invalid_argument &error)
    {
        std::cerr << "invalid character found in input string: \""
                  << error.what() << "\"\n";
    }
    catch (std::runtime_error &error)
    {
        std::cerr << error.what() << '\n';
    }
}