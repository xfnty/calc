#ifndef _CALC_AST_EXPRESSIONVISITORS_ASTPRINTER_H_
#define _CALC_AST_EXPRESSIONVISITORS_ASTPRINTER_H_

#include <string>
#include <cassert>
#include <cstdint>

#include <Calc/AST/ExpressionVisitor.h>


namespace Calc::AST::ExpressionVisitors {

    class ASTPrinter : public ExpressionVisitor {
    public:
        void VisitLiteralExpression(const LiteralExpression& expr) override;
        void VisitUnaryExpression(const UnaryExpression& expr) override;
        void VisitBinaryExpression(const BinaryExpression& expr) override;
        void VisitGroupingExpression(const GroupingExpression& expr) override;

        void Clear();
        const std::string& GetBuffer() const;

    private:
        std::string buffer;
    };

}


#endif
