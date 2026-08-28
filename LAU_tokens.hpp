#pragma once
#include <string>
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
    inline constexpr std::string string_true = "True";
    inline constexpr std::string string_false = "False";
}
namespace Operations
{
    enum class OperationsType
    {
        ASIGN,
        PLUS,
        MINUS
    };
    inline constexpr char string_asign = '=';
    inline constexpr char string_plus = '+';
    inline constexpr char string_minus = '-';
}