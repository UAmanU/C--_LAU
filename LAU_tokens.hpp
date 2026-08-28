#pragma once
#include <string>
#include <variant>
using lau_types = std::variant<long long, bool, std::string>;
namespace TokenData
{
    enum class TokenType
    {
        INT,
        STRING,
        BOOL,
        VARIABLE,
        OPERATIONS,
        UNKNOWN
    };

    struct Token
    {
        TokenType type;
        std::string value;
    };
}
namespace Bool
{
    enum class BoolType
    {
        TRUE,
        FALSE,
    };
    inline constexpr std::string string_true = "true";
    inline constexpr std::string string_false = "false";
}
namespace Operations
{
    enum class OperationsType
    {
        ASIGN = '=',
        PLUS = '+',
        MINUS = '-',
    };
}