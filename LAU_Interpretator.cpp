#include "LAU_Interpretator.h"
Interpretator::Interpretator(std::shared_ptr<ASTNode> block_node) : block_node(std::move(block_node)) {}
std::shared_ptr<ASTNode> Interpretator::interpret(Context &context)
{
    block_node->eval(context);

    return std::move(block_node);
}