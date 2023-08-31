#ifndef _CALC_TOKEN_H_
#define _CALC_TOKEN_H_


namespace Calc {

    enum class Token {
        Invalid,
        Number,         // '1024'
        Add,            // '+'
        Subtract,       // '-'
        Divide,         // '/'
        Multiply,       // '*'
        Mod,            // '%'
        Power,          // '^'
        OpenBracket,    // '('
        CloseBracket,   // ')'
    };

}


#endif
