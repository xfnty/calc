#ifndef _CALC_EXPRESSION_H_
#define _CALC_EXPRESSION_H_

#include <cmath>
#include <stack>
#include <string>
#include <memory>
#include <cassert>
#include <cstdint>

#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <Calc/Util.h>
#include <Calc/Token.h>


namespace Calc {

    class ExpressionVisitor;

    class Expression {
    public:
        virtual ~Expression() = default;
        virtual void Accept(ExpressionVisitor& visitor) const = 0;
    };

    using ExpressionPtr = std::shared_ptr<Expression>;

    class LiteralExpression;
    class UnaryExpression;
    class BinaryExpression;
    class GroupingExpression;
    class AbsoluteExpression;

    class ExpressionVisitor {
    public:
        virtual void VisitLiteralExpression(const LiteralExpression& expr) = 0;
        virtual void VisitUnaryExpression(const UnaryExpression& expr) = 0;
        virtual void VisitBinaryExpression(const BinaryExpression& expr) = 0;
        virtual void VisitGroupingExpression(const GroupingExpression& expr) = 0;
        virtual void VisitAbsoluteExpression(const AbsoluteExpression& expr) = 0;
    };

    class LiteralExpression : public Expression {
    public:
        const Token token;

        LiteralExpression(Token t) : token(t) {};
        void Accept(ExpressionVisitor& visitor) const override { visitor.VisitLiteralExpression(*this); }
    };

    class UnaryExpression : public Expression {
    public:
        const Token op;
        const ExpressionPtr expression;

        UnaryExpression(Token op, ExpressionPtr right) : op(op), expression(right) {}
        void Accept(ExpressionVisitor& visitor) const override { visitor.VisitUnaryExpression(*this); }
    };

    class BinaryExpression : public Expression {
    public:
        const Token op;
        const ExpressionPtr left;
        const ExpressionPtr right;

        BinaryExpression(const ExpressionPtr left, Token op, ExpressionPtr right) : op(op), left(left), right(right) {}
        void Accept(ExpressionVisitor& visitor) const override { visitor.VisitBinaryExpression(*this); }
    };

    class GroupingExpression : public Expression {
    public:
        const ExpressionPtr expression;

        GroupingExpression(ExpressionPtr expr) : expression(expr) {};
        void Accept(ExpressionVisitor& visitor) const override { visitor.VisitGroupingExpression(*this); }
    };

    class AbsoluteExpression : public GroupingExpression {
    public:
        AbsoluteExpression(ExpressionPtr expr) : GroupingExpression(expr) {};
        void Accept(ExpressionVisitor& visitor) const override { visitor.VisitAbsoluteExpression(*this); }
    };

}


#endif
