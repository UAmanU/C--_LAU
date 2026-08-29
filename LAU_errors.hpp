#pragma once
#include <stdexcept>
namespace Error
{
    class SyntaxError : std::runtime_error
    {
    public:
        SyntaxError(const std::string &message) : std::runtime_error(std::move(message)) {};
    };
    class ValueError : SyntaxError
    {
    public:
        ValueError(const std::string &message) : SyntaxError(std::move(message)) {};
    };
    class NameError : SyntaxError
    {
    public:
        NameError(const std::string &message) : SyntaxError(std::move(message)) {};
    };
    class ValueError : SyntaxError
    {
    public:
        ValueError(const std::string &message) : SyntaxError(std::move(message)) {};
    };
}