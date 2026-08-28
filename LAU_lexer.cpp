#include "LAU_lexer.h"
Lexer::Lexer(const std::string &text) : text_code(text) {};
std::vector<TokenData::Token> Lexer::get_tokens() const
{
    return tokens;
}
TokenData::TokenType Lexer::get_token_type(const auto &text) const
{
    if (std::isdigit(text))
    {
        return TokenData::TokenType::INT;
    }
    if (text == Bool::string_true || text == Bool::string_false)
    {
        return TokenData::TokenType::BOOL;
    }
    if (text.count("'") == 2)
    {
        return TokenData::TokenType::STRING;
    }
    if (text == Operations::string_asign || text == Operations::string_plus || text == Operations::string_minus)
    {
        return TokenData::TokenType::OPERATIONS;
    }
    return TokenData::TokenType::UNKNOWN; // How can i check is text a variable?
}
void Lexer::convert_to_tokens()
{
    for (int i = 0; i < text_code.size(); i++)
    {
        // i Don't know what to do here yet.
    }
}