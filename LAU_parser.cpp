#include "LAU_parser.h"
#include "LAU_errors.hpp"
Parser::Parser(std::vector<TokenData::Token> &tokens) : tokens(std::move(tokens)) {};
void Parser::next_token()
{
    position_in_tokens++;
}
bool Parser::is_tokens_end()
{
    return position_in_tokens >= tokens.size();
}
auto Parser::token_to_type(const TokenData::Token &token) const
{
    lau_types token_value_type;
    switch (token.type)
    {
    case TokenData::TokenType::BOOL:
        token_value_type = (token.value == "True" ? true : false);
        return token_value_type;
    case TokenData::TokenType::INT:
        token_value_type = (std::stoi(token.value));
        return token_value_type;
    case TokenData::TokenType::STRING:
        return token.value;
    }
    throw Error::ValueError("ValueError");
}
LAU::Memory Parser::get_symbols() const
{
    return symbols;
}
void Parser::parse()
{
    int length = tokens.size();
    while (!(is_tokens_end()))
    {
        TokenData::Token current = tokens[position_in_tokens];
        if (current.type == TokenData::TokenType::UNKNOWN)
        {
            std::string error_msg = current.value + " is not defined.";
            throw Error::NameError(error_msg);
            break;
        }
        if (current.type == TokenData::TokenType::VARIABLE)
        {
            TokenData::Token next_symbol = tokens[position_in_tokens + 1];
            if (next_symbol.type == TokenData::TokenType::OPERATIONS)
            {
                if (next_symbol.value == "=") // asignment
                {
                    lau_types var_value = token_to_type(current); // i need to work with Parser
                                                                  // cause now, it will crash in line like
                                                                  // num = 1 + 2
                                                                  // i think i need to add ; symbol to see the lines.
                    symbols.emplace(current, var_value);
                    position_in_tokens++;
                    continue;
                }
            }
        }
    }
}