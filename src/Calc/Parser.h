#ifndef _CALC_PARSER_H_
#define _CALC_PARSER_H_

#include <string>
#include <vector>

#include <tl/expected.hpp>

#include <Calc/Token.h>
#include <Calc/AST/Expression.h>

/*
    Associativity: (left-to-right/right-to-left)
        * /     Left
        + -     Left
        -       Right

    Precedence (priority, from the highest to lowest):
        Primary     - a number or a grouping
        Unary       - a possibly negated grouping or a number
        Factor      - multiplication, division
        Term        - addition, subtraction
        Expression  - any of the things above

    Grammar:
        Expression  -> Term
        Unary       -> "-" Primary
        Factor      -> Unary ( ("*" / "/") Unary )*     [TODO: make it a true left-recursive rule]
        Term        -> Factor ( ("+" / "-") Factor )*   [NOTE: references the rule with higher priority]
        Primary     -> NUMBER | "(" Expression ")"
*/
namespace Calc {

    class Parser {
    public:
        class Error {
        public:
            enum class Type {
            };

        public:
            Error();
        };

    public:
        static tl::expected<std::vector<AST::Expression>, Error> Parse(const std::vector<Token>& tokens);
    };

}


#endif
