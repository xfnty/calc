# Simple Calculator in C++

![preview.gif](.github/preview.gif)

## Building and Running
- Configure, build and run (after cloning the repo): `make`
- Configure CMake: `make c`
- Build the project: `make b`, `make build`
- Build and run: `make args="'-2 * 2 + -1.5'"`
- Run: `make r ...`
- Run using gdb: `make d args="'x + y'"`

`make configure build_type=Release` will disable debug messages.

## Credits & References
- [Crafting Interpreters](https://craftinginterpreters.com/) by Bob Nystrom
- [Catch2](https://github.com/catchorg/Catch2/)
- [expected](https://github.com/TartanLlama/expected)
- [fmt](https://github.com/fmtlib/fmt)
- [spdlog](https://github.com/gabime/spdlog)

## TODO
- Parser error messages
- More operators: `^`, `%`, `|...|`, `x!` ...
- Builtin constants: `PI`, `e`, etc.
- Builtin functions: `sin()`, `ctan()`, `ln()` ...
