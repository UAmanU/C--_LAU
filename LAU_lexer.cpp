#include "LAU_lexer.h"
#include <iostream>
#include "LAU_keysymbols.hpp"
Lexer::Lexer(std::string text) : text_code(std::move(text)) {};
std::vector<TokenData::Token> Lexer::get_tokens() const
{
    return tokens;
}
TokenData::TokenType Lexer::get_word_type(const auto &text) const
{
    if (text == Bool::string_true || text == Bool::string_false)
    {
        return TokenData::TokenType::BOOL;
    }
    return TokenData::TokenType::VARIABLE;
}
void Lexer::convert_to_tokens()
{
    size_t lenght = text_code.size();
    size_t i = 0;
    while (i < lenght)
    {
        char current = text_code[i];
        if (std::isspace(current)) // spaces
        {
            i++;
            continue;
        } // operations
        if (current == Key_symbols::line_separator)
        { // line separator ;
            tokens.push_back({TokenData::TokenType::KEYWORD, ";"});
            i++;
            continue;
        }
        if (current == static_cast<char>(Operations::OperationsType::PLUS))
        {
            tokens.push_back({TokenData::TokenType::OPERATIONS, "+"});
            i++;
            continue;
        }
        if (current == static_cast<char>(Operations::OperationsType::MINUS))
        {
            tokens.push_back({TokenData::TokenType::OPERATIONS, "-"});
            i++;
            continue;
        }
        if (current == static_cast<char>(Operations::OperationsType::ASIGN))
        {
            tokens.push_back({TokenData::TokenType::OPERATIONS, "="});
            i++;
            continue;
        }
        if (std::isdigit(current)) // integers
        {
            std::string number = "";
            number += current;
            while (i < lenght && (std::isdigit(i)))
            {
                char current = text_code[i];
                number += current;
                i++;
            }
            i++;
            tokens.push_back({TokenData::TokenType::INT, number});
            continue;
        }
        if (current == '\'') // strings
        {
            std::string word = "";
            while (i < lenght && (!std::isspace(text_code[i])))
            {
                word += text_code[i];
                i++;
            }

            tokens.push_back({TokenData::TokenType::STRING, word});
            i++;
            continue;
        }
        if (std::isalpha(current) || current == '_') // variables and bools
        {
            std::string word = "";
            while (i < lenght && (std::isalnum(text_code[i]) || text_code[i] == '_'))
            {
                word += text_code[i];
                i++;
                continue;
            }
            tokens.push_back({get_word_type(word), word});
            continue;
        }
        std::string unknown_symbol(1, current);
        tokens.push_back({TokenData::TokenType::UNKNOWN, unknown_symbol});
        i++;
    }
}