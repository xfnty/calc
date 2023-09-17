#ifndef _CALC_TOKEN_H_
#define _CALC_TOKEN_H_

#include <string>
#include <cstdint>


namespace Calc {

    class Token {
    public:
        enum class Type : int {
            Invalid,
            Number,         // '1024.5'
            // Operators
            Add,            // '+'
            Subtract,       // '-'
            Divide,         // '/'
            Multiply,       // '*'
            // Other
            OpenBracket,    // '('
            CloseBracket,   // ')'
        };

        // Use BetterEnums?
        static constexpr const char* Names[] = {
            "INVALID",
            "NUM",
            "+",
            "-",
            "/",
            "*",
            "(",
            ")",
        };

    public:
        const Type      type;
        const double   number;

        Token(Type type) : type(type), number(0) {}
        Token(double number) : type(Type::Number), number(number) {}

        bool operator ==(const Token& other) const {
            return type == other.type && number == other.number;
        }

        bool operator !=(const Token& other) const {
            return type != other.type || number != other.number;
        }
    };
}


#endif
