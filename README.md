# Simple Calculator in C++

![preview.gif](.github/preview.gif)

## Features
- REPL
- Floating-point numbers
- Mathematical constants: `Pi`, `e`
- Operators: `+`, `-`, `*`, `/`, `^`, `%`, `!`
- Grouping expressions: `(...)`, `|...|`

## Supported Grammar
```
NUMBER 	= \d+(\.\d+)?
ID 		= \w[_\w\d]+

Expression = Term
Term = Factor (("+" | "-") Factor)*
Factor = Unary (("*" | "/" | "^" | "%") Unary)*
Unary = ("-" | "!") Primary
Primary = NUMBER | ID | "(" Expression ")" | "|" Expression "|"

    Grammar:
        Primary     = NUMBER | ID | "(" Expression ")" | "|" Expression "|"
        Function    = ID "(" Expression ( "," Expression )* ")" | Primary
        Unary       = Function | ("-" Function) | (Function "!")
        Factor      = Unary (("*" | "/" | "^" | "%") Unary)*     [TODO: make it a true left-recursive rule]
        Term        = Factor (("+" | "-") Factor)*               [NOTE: references the rule with higher priority]
        Expression  = Term                                       [any use for that?]
```

## Building and Running
- All at once: `make`
- Configure CMake: `make c build_type=Debug`
- Build the project: `make b`
- Run: `make r`

## Credits & References
- [Crafting Interpreters](https://craftinginterpreters.com/) by Bob Nystrom
- [Catch2](https://github.com/catchorg/Catch2/)
- [expected](https://github.com/TartanLlama/expected)
- [fmt](https://github.com/fmtlib/fmt)
- [spdlog](https://github.com/gabime/spdlog)
- [cpp-linenoise](https://github.com/yhirose/cpp-linenoise)

## TODO
- Parser error messages
- Make macros in `Util.h` an inline functions
- Better stack-related error handling
  - Implement callstack frames
- Remove `else` blocks at the end of functions in `ExpressionEvaluator`
- Fix `^` operator and increase its precedence
- Better `std::string` usage
