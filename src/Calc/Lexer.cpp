#include <Calc/Lexer.h>

#include <fmt/format.h>
#include <tl/expected.hpp>

#include <Calc/Token.h>


namespace Calc {

    Lexer::Error::Error(const std::string& src, int pos, std::string desc, Lexer::Error::Type type)
    : source(src), position(pos), description(desc), type(type) {
    }

    tl::expected<std::vector<Token>, Lexer::Error> Lexer::Tokenize(const std::string& text) {
        std::vector<Token> tokens;

        int cursor = 0;
        while (cursor < text.size()) {
            char chr = text[cursor];

            if (chr == ' ' || chr == '\n' || chr == '\t' || chr == '\r') {
                cursor++;
                continue;
            }

            else if (chr == '+')
                tokens.push_back(Token(Token::Type::Add));
            else if (chr == '-')
                tokens.push_back(Token(Token::Type::Subtract));
            else if (chr == '*')
                tokens.push_back(Token(Token::Type::Multiply));
            else if (chr == '/')
                tokens.push_back(Token(Token::Type::Divide));
            else if (chr == '(')
                tokens.push_back(Token(Token::Type::OpenBracket));
            else if (chr == ')')
                tokens.push_back(Token(Token::Type::CloseBracket));

            else if (chr >= '0' && chr <= '9') {
                int64_t number = 0;
                do {
                    number *= 10;
                    number += text[cursor] - '0';
                    cursor++;
                    chr = text[cursor];
                }
                while (cursor < text.size() && chr >= '0' && chr <= '9');
                cursor--;

                tokens.push_back(Token(number));
            }

            else {
                return tl::unexpected(
                    Lexer::Error(
                        text,
                        cursor,
                        fmt::format("Invalid token '{}'", chr),
                        Lexer::Error::Type::InvalidToken
                    )
                );
            }

            cursor++;
        }

        return tokens;
    }

}
