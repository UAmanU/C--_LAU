#pragma once
#include "LAU_nodes.hpp"

// interpretator class may be not useful now because in mvp nodes can evaluate themselves.
class Interpretator
{
private:
    std::shared_ptr<ASTNode> block_node;

public:
    Interpretator(std::shared_ptr<ASTNode> block_node);
    ~Interpretator() = default;
    std::shared_ptr<ASTNode> interpret(Context &context); // returns block_node
};