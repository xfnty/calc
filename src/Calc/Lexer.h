#ifndef _CALC_LEXER_H_
#define _CALC_LEXER_H_

#include <string>
#include <vector>

#include <tl/expected.hpp>

#include <Calc/Token.h>


namespace Calc {

    class Lexer {
    public:
        class Error {
        public:
            enum class Type {
                InvalidToken,
            };

        public:
            Error(const std::string& source, int pos, std::string desc, Type type);

            const std::string&  source;
            const int           position;
            const std::string   description;
            const Type          type;
        };

    public:
        static tl::expected<std::vector<Token>, Error> Tokenize(const std::string& text);
    };

}


#endif
