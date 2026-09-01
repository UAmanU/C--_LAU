#pragma once
#include "LAU_nodes.hpp"

class Interpretator
{
private:
    std::unique_ptr<ASTNode> block_node;

public:
    Interpretator(std::unique_ptr<ASTNode> block_node) : block_node(std::move(block_node)) {}
    ~Interpretator() = default;
    std::unique_ptr<ASTNode> interpret(Context &context); // returns block_node
};