#ifndef _CALC_LEXER_H_
#define _CALC_LEXER_H_

#include <string>
#include <vector>

#include <tl/expected.hpp>

#include <Calc/Token.h>

namespace Calc {

    class Lexer {
    public:
        tl::expected<std::vector<Token>, std::string> Process(const std::string& text);
    };

}


#endif
