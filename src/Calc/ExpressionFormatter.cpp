#include <Calc/ExpressionFormatter.h>


namespace Calc {

    std::string ExpressionFormatter::Format(ExpressionPtr expr) {
        ExpressionFormatter formatter;
        expr->Accept(formatter);
        return formatter.buffer;
    }

    void ExpressionFormatter::VisitLiteralExpression(const LiteralExpression& expr) {
        buffer += (expr.token.type == Token::Type::Identifier)
            ? (expr.token.id)
            : (fmt::format("{}", expr.token.number));
    }

    void ExpressionFormatter::VisitUnaryExpression(const UnaryExpression& expr) {
        if (expr.op.type == Token::Type::Subtract)
            buffer += expr.op.ToString();
        
        buffer += "(";
        expr.expression->Accept(*this);
        buffer += ")";

        if (expr.op.type == Token::Type::Factorial)
            buffer += expr.op.ToString();
    }

    void ExpressionFormatter::VisitBinaryExpression(const BinaryExpression& expr) {
        buffer += "(";
        expr.left->Accept(*this);
        buffer += ")";
        buffer += expr.op.ToString();
        buffer += "(";
        expr.right->Accept(*this);
        buffer += ")";
    }

    void ExpressionFormatter::VisitGroupingExpression(const GroupingExpression& expr) {
        buffer += '(';
        expr.expression->Accept(*this);
        buffer += ')';
    }

    void ExpressionFormatter::VisitAbsoluteExpression(const AbsoluteExpression& expr) {
        buffer += '|';
        expr.expression->Accept(*this);
        buffer += '|';
    }

}
