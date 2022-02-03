/**
 * @file rpn_calculator.hpp
 * @author Nikita Mashtalirov (nik.mashtalirov@yandex.ru)
 * @brief Reverse polish notation (RPN)
 * @version 0.1
 * @date 2022-01-27
 * 
 * @copyright Copyright (c) 2022
 */

#include <stack>
#include <iterator>
#include <map>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <functional>

class reverse_polish_notation final
{
private:
    static std::map<std::string,
                    std::function<double(double, double)>>
        operators;

    static std::stack<double> storage;

public:
    template <typename input_iterator>
    static double
    evaluate(input_iterator first, input_iterator last)
    {
        for (; first != last; ++first)
        {
            std::stringstream stream{*first};
            if (auto value{0.0}; stream >> value)
            {
                storage.push(value);
            }
            else if (auto op{operators.find(*first)};
                     op != std::end(operators))
            {
                auto const right{get_top()};
                auto const left{get_top()};
                auto result{op->second(left, right)};
                storage.push(result);
            }
            else
            {
                throw std::invalid_argument{*first};
            }
        }
        if (storage.size() > 1UL)
        {
            throw std::runtime_error("incorrect number of "
                                     "operands and operators");
        }
        return storage.top();
    }

private:
    static double
    get_top()
    {
        auto value{storage.top()};
        storage.pop();
        return value;
    }
};

std::map<std::string,
         std::function<double(double, double)>>
    reverse_polish_notation::operators{
        {"+", [](double left, double right)
         { return left + right; }},
        {"-", [](double left, double right)
         { return left - right; }},
        {"*", [](double left, double right)
         { return left * right; }},
        {"/", [](double left, double right)
         { return left / right; }},
        {"^", [](double left, double right)
         { return std::pow(left, right); }},
        {"%", [](double left, double right)
         { return std::fmod(left, right); }},
    };

std::stack<double> reverse_polish_notation::storage;
