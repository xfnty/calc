#ifndef _CALC_PARSER_H_
#define _CALC_PARSER_H_

#include <string>
#include <vector>

#include <tl/expected.hpp>

#include <Calc/Token.h>


namespace Calc {

    class Parser {
    public:
        class Error {
        public:
            const std::string description;

            Error(const std::string& description);
        };

    public:
        tl::expected<std::vector<char>, Error> Process(const std::vector<Token>& tokens);
    };

}


#endif
