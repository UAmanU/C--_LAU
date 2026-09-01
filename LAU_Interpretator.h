#pragma once
#include "LAU_nodes.hpp"

class Interpretator
{
private:
    std::shared_ptr<ASTNode> block_node;

public:
    Interpretator(std::shared_ptr<ASTNode> block_node) : block_node(std::move(block_node)) {}
    ~Interpretator() = default;
    std::shared_ptr<ASTNode> interpret(Context &context); // returns block_node
};