#pragma once
#include <stdexcept>
namespace Error
{
    class SyntaxError : std::runtime_error
    {
    public:
        SyntaxError(const std::string &message) : std::runtime_error(message) {};
    };
    class ValueError : SyntaxError
    {
    public:
        ValueError(const std::string &message) : SyntaxError(message) {};
    };
    class NameError : SyntaxError
    {
    public:
        NameError(const std::string &message) : SyntaxError(message) {};
    };
    class ValueError : SyntaxError
    {
    public:
        ValueError(const std::string &message) : SyntaxError(message) {};
    };
    class ZeroDivisionError : SyntaxError
    {
    public:
        ZeroDivisionError(const std::string &message) : SyntaxError(message) {};
    };
}