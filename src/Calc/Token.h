#ifndef _CALC_TOKEN_H_
#define _CALC_TOKEN_H_

#include <string>
#include <cstdint>


namespace Calc {

    class Token {
    public:
        enum class Type : int {
            Invalid,
            Number,             // '1024.5'
            Identifier,         // 'asin'
            // Operators
            Add,                // '+'
            Subtract,           // '-'
            Divide,             // '/'
            Multiply,           // '*'
            Power,              // '^'
            Modulo,             // '%'
            Factorial,          // '!'
            // Other
            OpenBracket,        // '('
            CloseBracket,       // ')'
            StraightBracket,    // '|'
        };

        // FIXME: Use BetterEnums?
        static constexpr const char* Names[] = {
            "INVALID",
            "NUM",
            "ID",
            "+",
            "-",
            "/",
            "*",
            "^",
            "%",
            "!",
            "(",
            ")",
            "|",
        };

    public:
        const Type        type;
        const double      number;
        const std::string id;

        Token(Type type) : type(type), number(0) {}
        Token(double number) : type(Type::Number), number(number) {}
        Token(const std::string& id) : type(Type::Identifier), number(0), id(id) {}

        bool operator ==(const Token& other) const {
            return type == other.type && number == other.number && id == other.id;
        }

        bool operator !=(const Token& other) const {
            return !(*this == other);
        }
    };
}


#endif
