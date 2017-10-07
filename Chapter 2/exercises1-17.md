# Exercise 1
Trigraphs are used when the input device doesn't support the entire C's character set.

# Exercise 2
I would expect to see trigraphs in source code written in machines with enough characters. 

# Exercise 3
A newline is not equivalent to a space or tab during the preprocessing. Spaces and tabs are ignored, while a newline matters.

# Exercise 4
To continnue a long line.

# Exercise 5
A join happens.

# Exercise 6
Because the chars sequence */ terminates a comment and the compiler does not support nested comments.

# Exercise 7
31 characters for internal variables, six for external variables. The six character names must not rely on distinction between upper and lower case, either.

# Exercise 8
A declaration is a statement introducing the name and, possibly, the type of something. 

# Exercise 9
A definition is a declaration reserving storage for the entity being defined.

# Exercise 10
_Long double_.

# Exercise 11
_Long double_.

# Exercise 12
No, there aren't. Since long double allows a bigger values range and is more precise, there are no problems in upcast a _float_ or a _double_ to a _long double_.

# Exercise 13
Since _double_ is less precise than _long double_, downcasting may lead to overflow or undefined behaviour.

# Exercise 14
Undefined behaviour is completely unpredictable.

# Exercise 15
1) Signed int
2) Unsigned int or int, depending on the implementation.
3) Unsigned int
4) Long
5) Unsigned long
6) Long
7) Float
8) Float
9) Long double

# Exercise 16
1) i1 % i2
2) i1 % (int)f1
3) If either operand is negative, the sign is implementation defined, otherwise it is positive. This means that, even if both operands are negative, we cannot predict the sign.
4) It can represent both integral and floating point subtraction
5) ``i1 &= 0xf;``
6) ``i1 |= 0xf;``
7) ``i1 &= 0xf;``
8) ``i1 = ((i2 >> 4) & 0xf) | ((i2 & 0xf) << 4);``
9) The result is unpredictable.

# Exercise 17
1) ``(c = ((u * f) + 2.6L))``
``(char = (unsigned * float) + long double)``
``(int = float + long double)``
``(int = long double)``
``int``

2) ``(u += (((--f) / u) % 3))``
``unsigned += (float / unsigned) % int)``
``unsigned += float % int``
``unsigned += float``
``unsigned``

3) ``(i <<= (u * (- (++f)))``
``int <<= (unsigned * (float)``
``int <<= float``
``int``

4) ``(u = (((i + 3) + 4) + 3.1))``
``unsigned = (((int + int) + int) + double))``
``unsigned = (int + double)``
``unsigned = double``
``unsigned``

5) ``(u = (((3.1 + i) + 3) + 4))``
``unsigned = (((double + int) + int) + int)``
``unsigned = ((double + int) + int)``
``unsigned = (double + int)``
``unsigned = double``
``unsigned``

6) ``(c = ((i << (- (--f))) \& 0xf))``
``(char = ((int << (- (--float))) \& int ))``
``(char = ((int << (- float)) \& int ))``
``(char = ((int << float) \& int))``
``(char = (int \& int))``
``char``
