#ifndef _CALC_PARSER_H_
#define _CALC_PARSER_H_

#include <string>
#include <vector>
#include <initializer_list>

#include <tl/expected.hpp>

#include <Calc/Token.h>
#include <Calc/Expression.h>

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
        Primary     -> NUMBER | "(" Expression ")"
        Unary       -> "-" Primary
        Factor      -> Unary ( ("*" / "/") Unary )*     [TODO: make it a true left-recursive rule]
        Term        -> Factor ( ("+" / "-") Factor )*   [NOTE: references the rule with higher priority]
        Expression  -> Term                             [any use for that?]
*/
namespace Calc {

    class Parser {
    public:
        class Error {
        public:
            enum class Type {
                SyntaxError,
            };

        public:
            Error() {}
        };

    public:
        static tl::expected<Expression*, Error> Parse(const std::vector<Token>& tokens);

    private:
        const std::vector<Token>& tokens;
        int current_token_i = 0;

        Parser(const std::vector<Token>& tokens) : tokens(tokens) {};

        Expression* Term();
        Expression* Factor();
        Expression* Unary();
        Expression* Primary();

        void Advance(int token_count = 1);
        Token PeekToken(int offset = 0) const;

        // Check whether current token matches any of the given `tokens` and then `Advance()`
        bool MatchAnyToken(std::initializer_list<Token::Type> tokens);
    };

}


#endif
