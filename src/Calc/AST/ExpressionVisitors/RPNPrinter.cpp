#include <Calc/AST/ExpressionVisitors/RPNPrinter.h>

#include <fmt/core.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <Calc/AST/Expression.h>


namespace Calc::AST::ExpressionVisitors {

    void RPNPrinter::VisitLiteralExpression(const LiteralExpression& expr) {
        buffer += fmt::to_string(expr.number);
    }

    void RPNPrinter::VisitUnaryExpression(const UnaryExpression& expr) {
        expr.right.Accept(*this);
        buffer += " ";
        buffer += Token::Names[(int)expr.op.type];
    }

    void RPNPrinter::VisitBinaryExpression(const BinaryExpression& expr) {
        expr.left.Accept(*this);
        buffer += " ";
        expr.right.Accept(*this);
        buffer += " ";
        buffer += Token::Names[(int)expr.op.type];
    }

    void RPNPrinter::VisitGroupingExpression(const GroupingExpression& expr) {
        expr.inner.Accept(*this);
    }

    void RPNPrinter::Clear() {
        buffer.clear();
    }

    const std::string& RPNPrinter::GetBuffer() const {
        return buffer;
    }

}
