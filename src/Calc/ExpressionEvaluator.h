#ifndef _CALC_EXPRESSIONEVALUATOR_H_
#define _CALC_EXPRESSIONEVALUATOR_H_

#include <stack>
#include <string>

#include <tl/expected.hpp>

#include <Calc/Expression.h>


namespace Calc {

    class ExpressionEvaluator : public ExpressionVisitor {
    public:
        class Error {
        public:
            std::string description;
            Error(const std::string& description);
        };

        using EvaluationResult = tl::expected<Token::number_type, Error>;

    public:
        static EvaluationResult Evaluate(ExpressionPtr expr);

        void VisitLiteralExpression(const LiteralExpression& expr) override;
        void VisitUnaryExpression(const UnaryExpression& expr) override;
        void VisitBinaryExpression(const BinaryExpression& expr) override;
        void VisitGroupingExpression(const GroupingExpression& expr) override;
        void VisitAbsoluteExpression(const AbsoluteExpression& expr) override;
        void VisitFunctionExpression(const FunctionExpression& expr) override;

    private:
        const ExpressionPtr root;
        std::stack<Token::number_type> stack;
        
        // used as an error marker in Visitor pattern 
        // but eventually gets returned by Evaluate()
        EvaluationResult tmp_result;

        ExpressionEvaluator(ExpressionPtr expr);
    };

}


#endif
