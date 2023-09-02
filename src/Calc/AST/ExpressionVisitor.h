#ifndef _CALC_AST_EXPRESSIONVISITOR_H_
#define _CALC_AST_EXPRESSIONVISITOR_H_

#include <cassert>
#include <cstdint>


namespace Calc::AST {

    class LiteralExpression;
    class UnaryExpression;
    class BinaryExpression;
    class GroupingExpression;

    class ExpressionVisitor {
    public:
        virtual void VisitLiteralExpression(const LiteralExpression& expr) = 0;
        virtual void VisitUnaryExpression(const UnaryExpression& expr) = 0;
        virtual void VisitBinaryExpression(const BinaryExpression& expr) = 0;
        virtual void VisitGroupingExpression(const GroupingExpression& expr) = 0;
    };

}


#endif
