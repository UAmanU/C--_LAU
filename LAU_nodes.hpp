#pragma once
#include <unordered_map>
#include "LAU_tokens.hpp"
#include <memory>
#include <vector>
#include "LAU_errors.hpp"
using Context = std::unordered_map<std::string, lau_types>;
struct ASTNode
{
    virtual ~ASTNode() = default;
    virtual lau_types eval(Context &context) = 0;
};
struct BlockNode : public ASTNode
{
    std::vector<std::unique_ptr<ASTNode>> nodes;
    BlockNode(std::vector<std::unique_ptr<ASTNode>> nodes) : nodes(std::move(nodes)) {}
    void add_node(std::unique_ptr<ASTNode> node)
    {
        nodes.push_back(std::move(node));
    }
    lau_types eval(Context &context) override
    {
        if (nodes.empty())
        {
            throw Error::SyntaxError("Syntax Error: BlockNode is empty.");
        }
        for (auto &node : nodes)
        {
            node->eval(context);
        }

        return 0; // i Don't know what to return here, cause BlockNode can't return once single value.
    }
};
struct AssignNode : public ASTNode
{
    std::string var_name;
    std::unique_ptr<ASTNode> var_value;
    AssignNode(std::string var_name, std::unique_ptr<ASTNode> var_value) : var_name(std::move(var_name)), var_value(std::move(var_value)) {}
    lau_types eval(Context &context) override
    {
        lau_types value = var_value->eval(context);
        context[var_name] = value;
        return value;
    }
};
struct VarNode : public ASTNode
{
    std::string var_name;
    lau_types var_value;
    VarNode(std::string var_name, lau_types var_value) : var_name(std::move(var_name)), var_value(std::move(var_value)) {}
    lau_types eval(Context &context) override
    {
        context[var_name] = var_value;
        return var_value;
    }
};
struct MathNode : public ASTNode
{
    char operation;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    MathNode(char operation, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right) : operation(operation), left(std::move(left)), right(std::move(right)) {}
    lau_types eval(Context &context) override
    {
        int left_value = std::get<long long>(left->eval(context));
        int right_value = std::get<long long>(right->eval(context));
        switch (operation)
        {
        case '+':
            return left_value + right_value;
        case '-':
            return left_value - right_value;
        case '*':
            return left_value * right_value;
        case '/':
            if (right_value == 0)
            {
                throw Error::ValueError("ValueError: Division by zero.");
            }
            return left_value / right_value;
        default:
            throw Error::SyntaxError("Syntax Error: Invalid operation.");
        }
        return 0;
    }
};
struct NumberNode : public ASTNode
{
    lau_types value;
    NumberNode(long long value) : value(std::move(value)) {}
    lau_types eval(Context &context) override
    {
        return value;
    }
};