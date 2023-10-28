#ifndef _CALC_TOKEN_H_
#define _CALC_TOKEN_H_

#include <string>
#include <cassert>

#include <fmt/format.h>


namespace Calc {

    class Token {
    public:
        enum class Type : int {
            Invalid,
            Number,             // '1024.5'
            Identifier,         // 'asin', 'log2'
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
            Comma,              // ','
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
            ",",
        };

        using number_type = double;

    public:
        const Type        type;
        const number_type number;
        const std::string id;

        Token(Type type) : type(type), number(0) {}
        Token(number_type number) : type(Type::Number), number(number) {}
        Token(const std::string& id) : type(Type::Identifier), number(0), id(id) {}

        bool operator ==(const Token& other) const {
            return type == other.type && number == other.number && id == other.id;
        }

        bool operator !=(const Token& other) const {
            return !(*this == other);
        }

        std::string ToString() const {
            if (type == Token::Type::Number)
                return fmt::to_string(number);
            else if (type == Token::Type::Identifier)
                return id;

            assert((int)type >= 0 && (int)type < sizeof(Names)/sizeof(Names[0]));
            return Token::Names[(int)type];
        }
    };
}


#endif
