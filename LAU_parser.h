#pragma once
#include <vector>
#include "LAU_nodes.hpp"
class Parser
{
private:
    std::vector<TokenData::Token> tokens;
    size_t position_in_tokens = 0;
    std::shared_ptr<BlockNode> block_node;
    void next_token();    // position_in_tokens++;
    bool is_tokens_end(); // return position_in_tokens >= tokes.size();
    auto token_to_type(const TokenData::Token &token) const;
    void evaluate_variable_value(const std::vector<TokenData::Token> &eval_tokens); // e.g. evaluating 2+3 value

public:
    Parser(std::vector<TokenData::Token> tokens, std::shared_ptr<BlockNode> block_node);
    ~Parser() = default;
    void parse(); // main method
    std::shared_ptr<BlockNode> get_block_node() const;
};