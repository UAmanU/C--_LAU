#include "LAU_Interpretator.h"
Interpretator::Interpretator(std::unique_ptr<ASTNode> block_node) : block_node(std::move(block_node)) {}
std::unique_ptr<ASTNode> Interpretator::interpret(Context &context)
{
    int result = std::get<long long>(block_node->eval(context));
    
    return std::move(block_node);
}