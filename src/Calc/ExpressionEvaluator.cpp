#include <Calc/ExpressionEvaluator.h>

#include <Calc/Util.h>
#include <algorithm>
#include <cmath>


namespace Calc {

    // FIXME: Improve stack-related error handling

    ExpressionEvaluator::Error::Error(const std::string& description) : description(description) {}

    ExpressionEvaluator::ExpressionEvaluator(ExpressionPtr expr) : root(expr) {}

    ExpressionEvaluator::EvaluationResult ExpressionEvaluator::Evaluate(ExpressionPtr expr) {
        ExpressionEvaluator evaluator(expr);
     
        expr->Accept(evaluator);
        ASSERT_HAS_VALUE_PROPAGATE(evaluator.tmp_result);
        
        evaluator.tmp_result = evaluator.stack.top();
        evaluator.stack.pop();
        if (evaluator.stack.size() > 0)
            return tl::unexpected(Error("evaluation graph has multiple root nodes"));

        return evaluator.tmp_result;
    }

    void ExpressionEvaluator::VisitLiteralExpression(const LiteralExpression& expr) {
        if (expr.token.type == Token::Type::Number) {
            stack.push(expr.token.number);
        }
        else if (expr.token.type == Token::Type::Identifier) {
            switch (Hash(expr.token.id.c_str())) {
            case Hash("Pi"):    return stack.push(3.14159265358979323846); break;
            case Hash("Tau"):   return stack.push(6.28318530717958647692); break;
            case Hash("e"):     return stack.push(2.71828182845904523536); break;
            case Hash("g"):     return stack.push(9.8); break;
            default:
                tmp_result = tl::unexpected(Error(fmt::format("Unknown identifier \"{}\"", expr.token.id)));
            }
        }
        else {
            tmp_result = tl::unexpected(Error(fmt::format("literal expression was given a non-literal token \"{}\"", expr.token.ToString())));
        }
    }

    void ExpressionEvaluator::VisitUnaryExpression(const UnaryExpression& expr) {
        expr.expression->Accept(*this);
        ASSERT_HAS_VALUE_RETURN(tmp_result);

        if (expr.op.type == Token::Type::Subtract) {
            stack.top() = -stack.top();
        }
        else if (expr.op.type == Token::Type::Factorial) {
            auto v = stack.top();
            stack.pop();

            if (v < 0) {
                tmp_result = tl::unexpected(Error("Could not compute factorial of a negative number"));
                return;
            }

            stack.push(std::tgamma(v + 1));
        }
        else {
            tmp_result = tl::unexpected(Error(fmt::format("unary expression was given an incompatible token \"{}\"", expr.op.ToString())));
        }
    }

    void ExpressionEvaluator::VisitBinaryExpression(const BinaryExpression& expr) {
        expr.left->Accept(*this);
        ASSERT_HAS_VALUE_RETURN(tmp_result);

        expr.right->Accept(*this);
        ASSERT_HAS_VALUE_RETURN(tmp_result);

        auto b = stack.top();
        stack.pop();
        auto a = stack.top();
        stack.pop();

        switch (expr.op.type) {
        case Token::Type::Add:      stack.push(a + b); break;
        case Token::Type::Subtract: stack.push(a - b); break;
        case Token::Type::Multiply: stack.push(a * b); break;
        case Token::Type::Divide:   stack.push(a / b); break;
        case Token::Type::Power:    stack.push(std::pow(a, b)); break;
        case Token::Type::Modulo:   stack.push(std::fmod(a, b)); break;
        default:
            tmp_result = tl::unexpected(Error(fmt::format("binary expression was given an incompatible token \"{}\"", expr.op.ToString())));
            return;
        }
    }

    void ExpressionEvaluator::VisitGroupingExpression(const GroupingExpression& expr) {
        expr.expression->Accept(*this);
    }

    void ExpressionEvaluator::VisitAbsoluteExpression(const AbsoluteExpression& expr) {
        expr.expression->Accept(*this);
        ASSERT_HAS_VALUE_RETURN(tmp_result);

        stack.top() = std::abs(stack.top());
    }

    void ExpressionEvaluator::VisitFunctionExpression(const FunctionExpression& expr) {
    	for (auto& arg : expr.args) {
	        arg->Accept(*this);
	        ASSERT_HAS_VALUE_RETURN(tmp_result);
    	}

        switch (Hash(expr.id.id.c_str())) {
        case Hash("min"): {
            auto b = stack.top();
            stack.pop();
            auto a = stack.top();
            stack.pop();
            stack.push(std::min(a, b));
        } break;

        case Hash("max"): {
            auto b = stack.top();
            stack.pop();
            auto a = stack.top();
            stack.pop();
            stack.push(std::max(a, b));
        } break;

        case Hash("floor"): {
            stack.top() = std::floor(stack.top());
        } break;
        
        case Hash("ceil"): {
            stack.top() = std::ceil(stack.top());
        } break;

        case Hash("trunc"): {
            stack.top() = std::trunc(stack.top());
        } break;

        case Hash("sign"): {
            stack.top() = (stack.top() >= 0) ? (1) : (-1);
        } break;

        case Hash("clamp"): {
            auto c = stack.top();
            stack.pop();
            auto b = stack.top();
            stack.pop();
            auto a = stack.top();
            stack.pop();
            stack.push(std::clamp(a, b, c));
        } break;

        case Hash("exp"): {
            stack.top() = std::exp(stack.top());
        } break;

        case Hash("ln"): {
            stack.top() = std::log(stack.top());
        } break;

        case Hash("sqrt"): {
            stack.top() = std::sqrt(stack.top());
        } break;

        case Hash("sin"): {
            stack.top() = std::sin(stack.top());
        } break;

        case Hash("cos"): {
            stack.top() = std::cos(stack.top());
        } break;

        case Hash("tan"): {
            stack.top() = std::tan(stack.top());
        } break;

        case Hash("asin"): {
            stack.top() = std::asin(stack.top());
        } break;

        case Hash("acos"): {
            stack.top() = std::acos(stack.top());
        } break;

        case Hash("atan"): {
            stack.top() = std::atan(stack.top());
        } break;

        default:
            tmp_result = tl::unexpected(Error(fmt::format("unknown function \"{}\"", expr.id.ToString())));
            return;
        }
    }

}
