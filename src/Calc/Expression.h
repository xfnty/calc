#ifndef _CALC_EXPRESSION_H_
#define _CALC_EXPRESSION_H_

#include <spdlog/spdlog.h>

#include <Calc/Token.h>
#include "fmt/format.h"


namespace Calc {

    class ExpressionVisitor;

    class Expression {
    public:
        virtual ~Expression() = default;

        virtual void Accept(ExpressionVisitor& visitor) const = 0;
        virtual double Evaluate() const = 0;
    };

    class LiteralExpression;
    class UnaryExpression;
    class BinaryExpression;
    class GroupingExpression;

    class ExpressionVisitor {
    public:
        virtual void VisitLiteralExpression(const LiteralExpression* expr) = 0;
        virtual void VisitUnaryExpression(const UnaryExpression* expr) = 0;
        virtual void VisitBinaryExpression(const BinaryExpression* expr) = 0;
        virtual void VisitGroupingExpression(const GroupingExpression* expr) = 0;
    };

    class LiteralExpression : public Expression {
    public:
        const Token token;
        const double& number = token.number;

        LiteralExpression(Token t) : token(t) {};
        void Accept(ExpressionVisitor& visitor) const override { visitor.VisitLiteralExpression(this); }
        double Evaluate() const override { return number; }
    };

    class UnaryExpression : public Expression {
    public:
        const Token op;
        const Expression* const expression;

        UnaryExpression(Token op, Expression* right) : op(op), expression(right) {}
        void Accept(ExpressionVisitor& visitor) const override { visitor.VisitUnaryExpression(this); }
        double Evaluate() const override { return -expression->Evaluate(); }
    };

    class BinaryExpression : public Expression {
    public:
        const Token op;
        const Expression* const left;
        const Expression* const right;

        BinaryExpression(Expression* left, Token op, Expression* right)
        : op(op), left(left), right(right) {}
        void Accept(ExpressionVisitor& visitor) const override { visitor.VisitBinaryExpression(this); }
        double Evaluate() const override {
            double a = left->Evaluate();
            double b = right->Evaluate();
            switch (op.type) {
                case Token::Type::Add:      return a + b;
                case Token::Type::Subtract: return a - b;
                case Token::Type::Multiply: return a * b;
                case Token::Type::Divide:   return a / b;
                default: return 0;
            }
        }
    };

    class GroupingExpression : public Expression {
    public:
        const Expression* const expression;

        GroupingExpression(Expression* expr) : expression(expr) {};
        void Accept(ExpressionVisitor& visitor) const override { visitor.VisitGroupingExpression(this); }
        double Evaluate() const override { return expression->Evaluate(); }
    };

    class ExpressionPrinter : public ExpressionVisitor {
    public:
        std::string buffer;

        void VisitLiteralExpression(const LiteralExpression* expr) override {
            buffer += fmt::format("{}", expr->number);
        }

        void VisitUnaryExpression(const UnaryExpression* expr) override {
            buffer += "-(";
            expr->expression->Accept(*this);
            buffer += ")";
        }

        void VisitBinaryExpression(const BinaryExpression* expr) override {
            buffer += "(";
            expr->left->Accept(*this);
            buffer += ")";
            buffer += Token::Names[(int)expr->op.type];
            buffer += "(";
            expr->right->Accept(*this);
            buffer += ")";
        }

        void VisitGroupingExpression(const GroupingExpression* expr) override {
            buffer += "(";
            expr->expression->Accept(*this);
            buffer += ")";
        }
    };

}


#endif
