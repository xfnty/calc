#include <Calc/ExpressionEvaluator.h>


namespace Calc {

    ExpressionEvaluator::Error::Error(const std::string& description) : description(description) {}

    ExpressionEvaluator::ExpressionEvaluator(ExpressionPtr expr) : root(expr) {}

    tl::expected<double, ExpressionEvaluator::Error> ExpressionEvaluator::Evaluate(ExpressionPtr expr) {
        return tl::unexpected(Error("not implemented."));
    }

    void ExpressionEvaluator::VisitLiteralExpression(const LiteralExpression& expr) {
    }

    void ExpressionEvaluator::VisitUnaryExpression(const UnaryExpression& expr) {
    }

    void ExpressionEvaluator::VisitBinaryExpression(const BinaryExpression& expr) {
    }

    void ExpressionEvaluator::VisitGroupingExpression(const GroupingExpression& expr) {
    }

    void ExpressionEvaluator::VisitAbsoluteExpression(const AbsoluteExpression& expr) {
    }

}
