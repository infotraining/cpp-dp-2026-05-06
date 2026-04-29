#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <string>

namespace AST
{
    class ExpressionNode;
    class AddNode;
    class MultiplyNode;
    class IntNode;

    using ExpressionNodePtr = std::unique_ptr<ExpressionNode>;
    using AddNodePtr = std::unique_ptr<AddNode>;
    using MultiplyNodePtr = std::unique_ptr<MultiplyNode>;

    struct AstVisitor
    {
        virtual ~AstVisitor() = default;

        virtual void visit(AddNode& node) = 0;
        virtual void visit(MultiplyNode& node) = 0;
        virtual void visit(IntNode& node) = 0;
    };

    class ExpressionNode
    {
    public:
        virtual void accept(AstVisitor& v) = 0;
        virtual ~ExpressionNode() = default;
    };

    // CRTP for accept implementation in derived classes
    template <typename ExpressionType>
    class VisitableExpression : public ExpressionNode
    {
    public:
        void accept(AstVisitor& v)
        {
            v.visit(static_cast<ExpressionType&>(*this));
        }
    };

    class AddNode : public VisitableExpression<AddNode>
    {
        ExpressionNodePtr left_;
        ExpressionNodePtr right_;

    public:
        AddNode(ExpressionNodePtr left, ExpressionNodePtr right) : left_{std::move(left)}, right_{std::move(right)}
        {
        }

        ExpressionNode& left()
        {
            return *left_;
        }

        ExpressionNode& right()
        {
            return *right_;
        }
    };

    class MultiplyNode : public VisitableExpression<MultiplyNode>
    {
        ExpressionNodePtr left_;
        ExpressionNodePtr right_;

    public:
        MultiplyNode(ExpressionNodePtr left, ExpressionNodePtr right) : left_{std::move(left)}, right_{std::move(right)}
        {
        }

        ExpressionNode& left()
        {
            return *left_;
        }

        ExpressionNode& right()
        {
            return *right_;
        }
    };

    class IntNode : public VisitableExpression<IntNode>
    {
        int value_;

    public:
        IntNode(int value) : value_{value}
        {
        }

        int value() const
        {
            return value_;
        }
    };

    namespace helpers
    {
        AddNodePtr add(ExpressionNodePtr left, ExpressionNodePtr right)
        {
            return std::make_unique<AddNode>(std::move(left), std::move(right));
        }

        ExpressionNodePtr integer(int value)
        {
            return std::make_unique<IntNode>(value);
        }

        MultiplyNodePtr multiply(ExpressionNodePtr left, ExpressionNodePtr right)
        {
            return std::make_unique<MultiplyNode>(std::move(left), std::move(right));
        }
    }
}

#endif // AST_HPP