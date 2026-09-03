#include "LAU_parser.h"
#include <iostream>
Parser::Parser(std::vector<TokenData::Token> tokens, std::shared_ptr<BlockNode> block_node, const Context &context) : tokens(std::move(tokens)), block_node(std::move(block_node)), context(std::move(context)) {};

void Parser::move_position()
{
    position_in_tokens++;
    if (position_in_tokens > tokens.size() - 1)
    {
        return;
    }
    current_token = tokens[position_in_tokens];
    if (position_in_tokens > 0)
    {
        past_token = tokens[position_in_tokens - 1];
    }
    if (position_in_tokens < tokens.size() - 1)
    {
        next_token = tokens[position_in_tokens + 1];
    }
    else
    {
        next_token = TokenData::Token(TokenData::TokenType::UNKNOWN, "");
    }
}
bool Parser::is_tokens_end()
{
    return position_in_tokens >= tokens.size();
}
lau_types Parser::token_to_type(const TokenData::Token &token) const
{
    lau_types token_value_type;
    switch (token.type)
    {
    case TokenData::TokenType::BOOL:
        token_value_type = (token.value == "true" ? true : false);
        return token_value_type;
    case TokenData::TokenType::INT:
        token_value_type = (std::stoi(token.value));
        return token_value_type;
    case TokenData::TokenType::STRING:
        return token.value;
    }
    throw Error::ValueError("ValueError");
}
void Parser::evaluate_variable_value(std::vector<TokenData::Token> &eval_tokens)
{
    std::unique_ptr<ASTNode> assign_node;
    std::string var_name = tokens[position_in_tokens - eval_tokens.size() - 2].value;
    TokenData::TokenType result_type = eval_tokens[0].type;
    std::cout << "variable name: " + var_name + '\n';
    if (eval_tokens.size() == 1)
    {
        assign_node = std::make_unique<AssignNode>(var_name, std::make_unique<NumberNode>(std::stoll(eval_tokens[0].value)));
        block_node->add_node(std::move(assign_node));

        return;
    }

    for (int i = 1; i < eval_tokens.size() - 1; i++)
    {
        TokenData::Token current = eval_tokens[i];
        TokenData::Token next = eval_tokens[i + 1];
        TokenData::Token past = eval_tokens[i - 1];

        std::cout << "current: " << current.value << " next: " << next.value << " past: " << past.value << '\n';
        if (current.type == next.type || current.type == past.type)
        {
            throw Error::SyntaxError("Syntax Error");
        }
        if (current.type == TokenData::TokenType::OPERATIONS)
        {
            if (past.type != next.type && past.type != TokenData::TokenType::INT)
            {
                // MVP can only sum integers.
                std::cout << "error is going to corrupt.\n";
                throw Error::ValueError("You can work with only numbers.");
            }
            std::cout << "Func is there.\n";
            std::unique_ptr<ASTNode> next_number_node = std::make_unique<NumberNode>(std::stoll(next.value));
            std::unique_ptr<ASTNode> past_number_node = std::make_unique<NumberNode>(std::stoll(past.value));
            std::unique_ptr<ASTNode> math_node = std::make_unique<MathNode>(current.value[0], std::move(past_number_node), std::move(next_number_node));
            eval_tokens[i] = {TokenData::TokenType::INT, std::to_string(std::get<long long>(math_node->eval(context)))};
            std::cout << eval_tokens[i].value << '\n';
            assign_node = std::make_unique<AssignNode>(var_name, std::move(math_node));
            block_node->add_node(std::move(assign_node));
            std::erase(eval_tokens, past);
            std::erase(eval_tokens, current);
            std::erase(eval_tokens, next);
            i++;
        }
    }
    std::cout << "Func ended.\n";
    return;
}
void Parser::parse()
{

    int length = tokens.size();
    current_token = tokens[position_in_tokens];
    next_token = tokens[position_in_tokens + 1];
    while (!(is_tokens_end()))
    {
        current_token = tokens[position_in_tokens];
        if (current_token.type == TokenData::TokenType::UNKNOWN)
        {
            std::string error_msg = current_token.value + " is not defined.";
            throw Error::NameError(error_msg);
        }
        if (current_token.type == TokenData::TokenType::KEYWORD)
        {
            move_position();
            continue;
        }
        if (current_token.type == TokenData::TokenType::VARIABLE)
        {
            std::cout << "New variable to evaluate: " + current_token.value + '\n';
            if (next_token.type == TokenData::TokenType::OPERATIONS)
            {
                if (next_token.value == "=") // assignment
                {
                    move_position();
                    if (next_token.type == TokenData::TokenType::BOOL)
                    {
                        block_node->add_node(std::make_unique<AssignNode>(past_token.value, std::make_unique<VarNode>(past_token.value, token_to_type(next_token))));
                        move_position();
                        std::cout << "Added a bool variable. Current token is: " + current_token.value + '\n';
                    }
                    else
                    {
                        std::vector<TokenData::Token> eval_tokens;
                        move_position(); // variable name and = shouldn't be in eval_tokens
                        std::cout << "evaluating eval_tokens for variable: " + current_token.value + '\n';
                        while (current_token.value != ";")
                        {
                            std::cout << "pushing " << current_token.value << " to eval tokens...\n";
                            eval_tokens.push_back({current_token.type, current_token.value});
                            move_position();
                        }
                        evaluate_variable_value(eval_tokens);
                        move_position();
                        continue;
                    }
                    std::cout << "Succesfully evaluated variable. current token: " + current_token.value + '\n';
                    move_position();
                    continue;
                }
                else
                {
                    std::string error_msg = "SyntaxError: invalid asignment for variable.";
                    throw Error::NameError(error_msg);
                }
            }
            else
            {
                throw Error::SyntaxError("Syntax Error. No assignment");
            }
        }
        // my planned MVP version of code only can create variables, not references, functions.
        else
        {
            throw Error::SyntaxError("Syntax Error. There're no variables to create in context ");
        }
    }
}
std::shared_ptr<BlockNode> Parser::get_block_node() const
{
    return block_node;
}