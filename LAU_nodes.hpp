#pragma once
#include <unordered_map>
#include "LAU_tokens.hpp"
#include <memory>
#include "LAU_errors.hpp"
using Context = std::unordered_map<std::string, lau_types>;
struct ASTNode
{
    virtual ~ASTNode() = default;
    virtual lau_types eval(Context &context) = 0;
};
struct BlockNode : ASTNode
{
    std::vector<ASTNode> nodes;
    BlockNode() = default;
    void add_node(std::unique_ptr<ASTNode> node)
    {
        nodes.push_back(std::move(*node));
    }
    lau_types eval(Context &context) override
    {
        lau_types result;
        for (auto &node : nodes)
        {
            result = node.eval(context);
        }
        return result;
    }
};
struct AssignmentNode : ASTNode
{
    std::string var_name;
    std::unique_ptr<ASTNode> expression;
    AssignmentNode(std::string var_name, std::unique_ptr<ASTNode> var_expression) : var_name(std::move(var_name)), expression(std::move(var_expression)) {};
    lau_types eval(Context &context) override
    {
        lau_types expression_value = expression->eval(context);
        context[var_name] = expression_value;
        return expression_value;
    }
};
struct MathNode : ASTNode
{
    char op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    MathNode(char op, std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r) : op(op), left(std::move(l)), right(std::move(r)) {};
    lau_types eval(Context &context) override
    {
        long long l_result = std::get<long long>(left->eval(context));
        long long r_result = std::get<long long>(right->eval(context));
        lau_types result = 0;
        switch (op)
        {
        case '+':
            result = l_result + r_result;
            break;
        case '-':
            result = l_result - r_result;
            break;
        case '*':
            result = l_result * r_result;
            break;
        case '/':
            if (r_result == 0)
            {
                throw Error::ZeroDivisionError("You can't divide on zero.");
            }
            result = l_result / r_result;
            break;
        }
        return result;
    }
};
struct VariableNode : ASTNode
{
    std::string var_name;
    VariableNode(const std::string &name) : var_name(name) {};
    lau_types eval(Context &context) override
    {
        auto it = context.find(var_name);
        if (it != context.end())
        {
            return it->second;
        }
        throw Error::NameError("Name Error.");
    }
};
struct NumberNode : ASTNode
{
    long long num;
    NumberNode(long long num) : num(num) {};
    lau_types eval(Context &context) override
    {
        return num;
    }
};
