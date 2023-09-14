#include <Calc/Parser.h>

#include <fmt/format.h>
#include <tl/expected.hpp>


namespace Calc {

    Parser::Error::Error() {}

    tl::expected<std::vector<AST::Expression>, Parser::Error> Parser::Parse(const std::vector<Token>& tokens) {
        return tl::unexpected(Parser::Error());
    }

}
