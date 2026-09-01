#pragma once
#include <stdexcept>
namespace Error
{
    class SyntaxError : std::runtime_error
    {
    public:
        SyntaxError(const std::string &message) : std::runtime_error(message) {};
    };
    class ValueError : std::runtime_error
    {
    public:
        ValueError(const std::string &message) : std::runtime_error(message) {};
    };
    class NameError : std::runtime_error
    {
    public:
        NameError(const std::string &message) : std::runtime_error(message) {};
    };
    class ValueError : std::runtime_error
    {
    public:
        ValueError(const std::string &message) : std::runtime_error(message) {};
    };
    class ZeroDivisionError : std::runtime_error
    {
    public:
        ZeroDivisionError(const std::string &message) : std::runtime_error(message) {};
    };
}