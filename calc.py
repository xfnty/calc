#!/usr/bin/python3

import sys
from typing_extensions import override


"""

Tokens: "+", "*", "0", "1", ... "9"

Grammar:
    Primary        = Number | Multiplication
    Multiplication = Primary ("*" Primary)*
    Addition       = Multiplication ("+" Multiplication)*

Expressions:
    NumberExpression - a single digit
    BinaryExpression - an expression with 2 operands and an operator

"""


RESET, BRIGHT, RED, WHITE, CYAN = '', '', '', '', ''
try: import colorama; RESET, BRIGHT, RED, WHITE, CYAN = colorama.Style.RESET_ALL, colorama.Style.BRIGHT, colorama.Fore.RED, colorama.Fore.WHITE, colorama.Fore.CYAN
except: pass

def error(*args):
    print(f'{BRIGHT+RED}error{WHITE}:', *args, RESET)
    quit()

def debug_note(title, *args):
    print(f'{WHITE}{title}:', *args, RESET)


def tokenize(string):
    tokens = []
    cursor = 0

    while cursor < len(string):
        if string[cursor].isspace():
            cursor += 1
            continue

        if string[cursor] not in '+*0123456789':
            error(f'Invalid token `{string[cursor]}`')

        tokens.append(string[cursor])
        cursor += 1

    return tokens


class Expression: 
    def eval(self): ...
    def __str__(self): ...


class NumberExpression(Expression):
    def __init__(self, token):
        self.token = token

    @override
    def eval(self):
        return int(self.token)

    @override
    def __str__(self):
        return self.token


class BinaryExpression(Expression):
    def __init__(self, left, op, right):
        self.left = left
        self.op = op
        self.right = right

    @override
    def eval(self):
        a = self.left.eval()
        b = self.right.eval()

        if self.op == '+':
            return a + b
        return a * b

    @override
    def __str__(self):
        return f'({self.left}){self.op}({self.right})'


def parse(tokens):
    cursor = 0

    def match(possible_tokens, offset=0):
        if cursor + offset not in range(len(tokens)):
            return False
        return tokens[cursor + offset] in possible_tokens

    def parse_number():
        nonlocal cursor

        if match('0123456789'):
            expr = NumberExpression(tokens[cursor])
            cursor += 1
            return expr
        
        error(f'Expected number at {cursor}')

    def parse_multipliaction():
        nonlocal cursor

        expr = parse_number()
        
        while match('*'):
            cursor += 1
            right = parse_number()
            expr = BinaryExpression(expr, '*', right)
        
        return expr

    def parse_addition():
        nonlocal cursor
        
        expr = parse_multipliaction()
        
        while match('+'):
            cursor += 1
            right = parse_multipliaction()
            expr = BinaryExpression(expr, '+', right)
        
        return expr
    
    return parse_addition()


if __name__ == '__main__':
    string = ' '.join(sys.argv[1:])
    debug_note('string', f'"{string}"')

    tokens = tokenize(string)
    debug_note('tokens', f'[{", ".join(tokens)}]')
    
    root = parse(tokens)
    debug_note('tree', root)
    
    print(root.eval())
