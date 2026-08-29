#pragma once
#include "LAU_tokens.hpp"
#include <vector>
#include <unordered_map>
namespace LAU
{
    using Memory = std::unordered_map<std::string, lau_types>;
}
class Parser
{
private:
    std::vector<TokenData::Token> tokens;
    size_t position_in_tokens = 0;
    LAU::Memory symbols;
    void next_token();    // position_in_tokens++;
    bool is_tokens_end(); // return position_in_tokens >= tokes.size();
    auto token_to_type(const TokenData::Token &token) const;

public:
    Parser(std::vector<TokenData::Token> &tokens);
    ~Parser() = default;
    void parse();                    // main method
    LAU::Memory get_symbols() const; // return symbols;
};