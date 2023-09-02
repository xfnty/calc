#ifndef _CALC_AST_EXPRESSION_H_
#define _CALC_AST_EXPRESSION_H_

#include <cassert>
#include <cstdint>

#include <Calc/Token.h>
#include <Calc/AST/ExpressionVisitor.h>


/*
 * Grammar rules:
 *     expression = literal | unary | binary | grouping
 *
 *     literal = NUMBER
 *     operator = "+" | "-" | "*" | "/"
 *
 *     grouping = "(" expression ")"
 *     unary = "-" (literal | grouping)
 *     binary = expression operator expression
 */
namespace Calc::AST {

    class Expression {
    public:
        virtual void Accept(ExpressionVisitor& visitor) const = 0;
    };

    class LiteralExpression : public Expression {
    public:
        const Token    token;
        const int64_t& number = token.number;
        LiteralExpression(Token token) : token(token) {
            assert(token.type == Token::Type::Number);
        }
        void Accept(ExpressionVisitor& visitor) const override {
            visitor.VisitLiteralExpression(*this);
        }
    };

    class GroupingExpression : public Expression {
    public:
        const Expression& inner;
        GroupingExpression(const Expression& inner) : inner(inner) {}
        void Accept(ExpressionVisitor& visitor) const override {
            visitor.VisitGroupingExpression(*this);
        }
    };

    class UnaryExpression : public Expression {
    public:
        const Token       op;
        const Expression& right;
        UnaryExpression(Token token, const Expression& right) : op(token), right(right) {
            assert(op.type == Token::Type::Subtract);
        }
        void Accept(ExpressionVisitor& visitor) const override {
            visitor.VisitUnaryExpression(*this);
        }
    };

    class BinaryExpression : public Expression {
    public:
        const Expression& left;
        const Expression& right;
        const Token       op;
        BinaryExpression(const Expression& left, Token op, const Expression& right)
        : left(left), op(op), right(right) {
            assert(
                op.type == Token::Type::Add ||
                op.type == Token::Type::Subtract ||
                op.type == Token::Type::Multiply ||
                op.type == Token::Type::Divide
            );
        }
        void Accept(ExpressionVisitor& visitor) const override {
            visitor.VisitBinaryExpression(*this);
        }
    };

}

#endif
