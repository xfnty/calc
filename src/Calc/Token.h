#ifndef _CALC_TOKEN_H_
#define _CALC_TOKEN_H_

#include <string>
#include <cstdint>


namespace Calc {

    class Token {
    public:
        enum class Type : int {
            Invalid,
            Number,         // '1024'
            // Operators
            Add,            // '+'
            Subtract,       // '-'
            Divide,         // '/'
            Multiply,       // '*'
            // Other
            OpenBracket,    // '('
            CloseBracket,   // ')'
        };

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
        const int64_t   number;

        Token(Type type) : type(type), number(0) {}
        Token(int64_t number) : type(Type::Number), number(number) {}

        bool operator ==(const Token& other) const {
            return type == other.type && number == other.number;
        }

        bool operator !=(const Token& other) const {
            return type != other.type || number != other.number;
        }
    };
}


#endif
