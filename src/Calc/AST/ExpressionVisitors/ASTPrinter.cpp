#include <Calc/AST/ExpressionVisitors/ASTPrinter.h>

#include <fmt/core.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <Calc/AST/Expression.h>


namespace Calc::AST::ExpressionVisitors {

    void ASTPrinter::VisitLiteralExpression(const LiteralExpression& expr) {
        buffer += fmt::to_string(expr.number);
    }

    void ASTPrinter::VisitUnaryExpression(const UnaryExpression& expr) {
        buffer += Token::Names[(int)expr.op.type];
        expr.right.Accept(*this);
    }

    void ASTPrinter::VisitBinaryExpression(const BinaryExpression& expr) {
        expr.left.Accept(*this);
        buffer += " ";
        buffer += Token::Names[(int)expr.op.type];
        buffer += " ";
        expr.right.Accept(*this);
    }

    void ASTPrinter::VisitGroupingExpression(const GroupingExpression& expr) {
        buffer += "(";
        expr.inner.Accept(*this);
        buffer += ")";
    }

    void ASTPrinter::Clear() {
        buffer.clear();
    }

    const std::string& ASTPrinter::GetBuffer() const {
        return buffer;
    }

}
