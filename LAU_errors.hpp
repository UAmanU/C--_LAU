#pragma once
#include <stdexcept>
namespace Error
{
    class SyntaxError : public std::runtime_error
    {
    public:
        SyntaxError(const std::string &message) : std::runtime_error(message) {};
    };
    class ValueError : public std::runtime_error
    {
    public:
        ValueError(const std::string &message) : std::runtime_error(message) {};
    };
    class NameError : public std::runtime_error
    {
    public:
        NameError(const std::string &message) : std::runtime_error(message) {};
    };
    class ZeroDivisionError : public std::runtime_error
    {
    public:
        ZeroDivisionError(const std::string &message) : std::runtime_error(message) {};
    };
}