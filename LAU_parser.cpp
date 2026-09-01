#include "LAU_parser.h"
// i need to work with Parser
// cause now, it will crash in line like
// num = 1 + 2
// i think i need to add ; symbol to see the lines.

Parser::Parser(std::vector<TokenData::Token> tokens) : tokens(std::move(tokens)) {}

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
lau_types Parser::evaluate_variable_value(const std::vector<TokenData::Token> &eval_tokens)
{
    TokenData::TokenType result_type = eval_tokens[0].type;
    for (int i = 1; i < eval_tokens.size(); i++)
    {
        TokenData::Token current = eval_tokens[i];
        TokenData::Token next = eval_tokens[i + 1];
        TokenData::Token past = eval_tokens[i - 1];
        if (current.type == next.type || current.type == past.type)
        {
            throw Error::SyntaxError("Syntax Error");
        }
        if (current.type == TokenData::TokenType::OPERATIONS)
        {
            if (past.type != next.type && past.type != TokenData::TokenType::INT)
            {
                // MVP can only sum integers.
                throw Error::ValueError("You can work with only numbers.");
            }
            std::unique_ptr<ASTNode> next_number_node = std::make_unique<NumberNode>(next.value);
            std::unique_ptr<ASTNode> past_number_node = std::make_unique<NumberNode>(past.value);
            std::unique_ptr<ASTNode> math_node = std::make_unique<MathNode>(current.value, past_number_node, next_number_node);
            block_node->add_node(std::move(math_node));
            return 0; //code ended succesfully.
        }
    }
    throw Error::SyntaxError("Syntax Error.");
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
                    std::vector<TokenData::Token> eval_tokens;
                    while (tokens[position_in_tokens].value != ";")
                    {
                        current = tokens[position_in_tokens];
                        eval_tokens.push_back({current.type, current.value});
                        position_in_tokens++;
                    }
                    lau_types var_value = evaluate_variable_value(eval_tokens);
                }
                else
                {
                    std::string error_msg = "SyntaxError: invalid asignment. for variable " + current.value;
                    throw Error::NameError(error_msg);
                }
                position_in_tokens++;
                continue;
            }
        }
        // my planned MVP version of code only can create variables, not references, functions.
        else
        {
            throw Error::SyntaxError("Invalid syntax.");
        }
    }
}