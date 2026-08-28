#pragma once
#include "LAU_tokens.hpp"
#include <vector>
class Lexer
{
private:
    std::vector<TokenData::Token> tokens;
    std::string text_code;

public:
    Lexer(const std::string &text_code); // takes file.txt's data to text_code attribute

    ~Lexer() = default; // default destructor

    void convert_to_tokens();                                    // analyses text_code and adds tokens to tokens attribute
    TokenData::TokenType get_token_type(const auto &text) const; // returns string's type.  e.g. get_text_type("2") = TokenData::TokenType::INT or get_text_type("'2'") = TokenData::TokenType::STRING
    std::vector<TokenData::Token> get_tokens() const;            // getter for tokens attribute.
};