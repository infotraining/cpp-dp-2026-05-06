#ifndef VISITORS_HPP
#define VISITORS_HPP

#include "ast.hpp"

class ExpressionEvaluator : public AST::AstVisitor
{
    int result_{};

public:
    void visit(AST::AddNode& node)
    {
        ExpressionEvaluator lv, rv;
        node.left().accept(lv);
        node.right().accept(rv);
        result_ = lv.result() + rv.result();
    }

    void visit(AST::MultiplyNode& node)
    {
        ExpressionEvaluator lv, rv;
        node.left().accept(lv);
        node.right().accept(rv);
        result_ = lv.result() * rv.result();
    }

    void visit(AST::IntNode& node)
    {
        result_ = node.value();
    }

    int result() const
    {
        return result_;
    }
};

// TODO: Implement visitor that prints expression to string
class PrintingVisitor
{
};

#endif // VISITORS_HPP