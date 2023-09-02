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
            Modulo,         // '%'
            Power,          // '^'
            // Other
            OpenBracket,    // '('
            CloseBracket,   // ')'
        };

        static constexpr const char* Names[] = {
            "Invalid",
            "Number",
            "Add",
            "Subtract",
            "Divide",
            "Multiply",
            "Modulo",
            "Power",
            "OpenBracket",
            "CloseBracket",
        };

    public:
        const Type      type;
        const int64_t   number;

        Token(Type type, int64_t number = 0) : type(type), number(number) {}

        bool operator ==(const Token& other) const {
            return type == other.type && number == other.number;
        }

        bool operator !=(const Token& other) const {
            return type != other.type || number != other.number;
        }
    };
}


#endif
