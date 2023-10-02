#ifndef _CALC_EXPRESSIONFORMATTER_H_
#define _CALC_EXPRESSIONFORMATTER_H_

#include <string>

#include <tl/expected.hpp>

#include <Calc/Expression.h>


namespace Calc {
    
    class ExpressionFormatter : public ExpressionVisitor {
    public:
        static std::string Format(ExpressionPtr expr);

        void VisitLiteralExpression(const LiteralExpression& expr) override;
        void VisitUnaryExpression(const UnaryExpression& expr) override;
        void VisitBinaryExpression(const BinaryExpression& expr) override;
        void VisitGroupingExpression(const GroupingExpression& expr) override;
        void VisitAbsoluteExpression(const AbsoluteExpression& expr) override;

    private:
        std::string buffer;
        
        ExpressionFormatter() = default;
    };

}


#endif
