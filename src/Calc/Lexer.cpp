#include <Calc/Lexer.h>

#include <array>
#include <algorithm>

#include <fmt/format.h>
#include <tl/expected.hpp>
#include <spdlog/spdlog.h>

#include <Calc/Token.h>


namespace Calc {

    struct TokenOp {
        char symbol;
        Token::Type token_type;
    };

    static const std::array<TokenOp, 10> token_table{{
        {'+', Token::Type::Add},
        {'-', Token::Type::Subtract},
        {'*', Token::Type::Multiply},
        {'/', Token::Type::Divide},
        {'^', Token::Type::Power},
        {'%', Token::Type::Modulo},
        {'!', Token::Type::Factorial},
        {'(', Token::Type::OpenBracket},
        {')', Token::Type::CloseBracket},
        {'|', Token::Type::StraightBracket},
    }};

    Lexer::Error::Error(const std::string& src, int pos, std::string desc, Lexer::Error::Type type)
    : source(src), position(pos), description(desc), type(type) {
    }

    tl::expected<std::vector<Token>, Lexer::Error> Lexer::Tokenize(const std::string& text) {
        std::vector<Token> tokens;

        int cursor = 0;
        while (cursor < text.size()) {
            std::array<TokenOp, 10>::const_iterator it;

            if (text[cursor] == ' ' || text[cursor] == '\n' || text[cursor] == '\t' || text[cursor] == '\r') {
                cursor++;
                continue;
            }

            if (text[cursor] >= '0' && text[cursor] <= '9') {
                double number = 0;
                do {
                    number *= 10;
                    number += text[cursor] - '0';
                    cursor++;
                }
                while (cursor < text.size() && (text[cursor] >= '0' && text[cursor] <= '9'));

                if (text[cursor] == '.') {
                    cursor++;

                    double fp = 1;
                    while (cursor < text.size() && (text[cursor] >= '0' && text[cursor] <= '9')) {
                        number += (text[cursor] - '0') / (10.0 * fp);
                        cursor++;
                        fp *= 10;
                    }
                }

                tokens.push_back(Token(number));
                cursor--;
            }
            else if (text[cursor] == '_' || (text[cursor] >= 'a' && text[cursor] <= 'z') || (text[cursor] >= 'A' && text[cursor] <= 'Z')) {
                std::string id;
                do {
                    id.push_back(text[cursor]);
                    cursor++;
                } while (text[cursor] == '_' || (text[cursor] >= 'a' && text[cursor] <= 'z') || (text[cursor] >= 'A' && text[cursor] <= 'Z'));
                tokens.push_back(Token(id));
                cursor--;
            }
            else if ((it = std::find_if(token_table.begin(), token_table.end(), [=](TokenOp t){ return text[cursor] == t.symbol; })) != token_table.end()) {
                tokens.push_back(Token(it->token_type));
            }
            else {
                return tl::unexpected(
                    Lexer::Error(
                        text,
                        cursor,
                        fmt::format("Invalid token '{}'", text[cursor]),
                        Lexer::Error::Type::InvalidToken
                    )
                );
            }

            cursor++;
        }

        return tokens;
    }

}
