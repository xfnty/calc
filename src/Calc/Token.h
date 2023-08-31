#ifndef _CALC_TOKEN_H_
#define _CALC_TOKEN_H_

#include <string>


namespace Calc {

    class Token {
    public:
        enum class Type : int {
            Invalid,
            Number,         // '1024'
            Add,            // '+'
            Subtract,       // '-'
            Divide,         // '/'
            Multiply,       // '*'
            Modulo,         // '%'
            Power,          // '^'
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
        const Type  type;
        const int   number;

        Token(Type type, int number = 0) : type(type), number(number) {}
    };
}


#endif
