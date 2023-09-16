# Simple Calculator in C++

## Usage
```
make args="'1 + 2 * (3 + 4) + 0.05'"
```
Output:
```
debug: expression="1 + 2 * (3 + 4) + 0.05"
debug: tokens=[1, +, 2, *, (, 3, +, 4, ), +, 0.05]
debug: ptr: 0x557b2899e710
order: ((1)+((2)*((3)+(4))))+(0.05)
result: 15.05
```
