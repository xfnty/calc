#include <Calc/Parser.h>


namespace Calc {

    Parser::Error::Error(const std::string& description) : description(description) {
    }

    tl::expected<std::vector<char>, Parser::Error> Parser::Process(const std::vector<Token>& tokens) {
        return tl::unexpected(Parser::Error("Not implemented"));
    }

}
