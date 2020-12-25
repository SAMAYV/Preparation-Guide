1)A signed variable of n bits can contain any integer between −2^n−1 and 2^(n−1)−1. For example, the int type in C++ is a signed type, so an int variable can contain any integer between −2^31 and 2^31 −1. The first bit in a signed representation is the sign of the number (0 for nonnegative numbers and 1 for negative numbers), and the remaining n−1 bits contain the magnitude of the number.

2)Two’s complement is used, which means that the opposite number of a number is calculated by first inverting all the bits in the number, and then increasing the number by one. For example, the bit representation of the int number −43 is
11111111111111111111111111010101.

3)An unsigned variable of n bits can contain any integer between 0 and 2^n −1. For example, in C++, an unsigned int variable can contain any integer between 0 and 2^32 −1.

4)a signed number −x
equals an unsigned number 2^n −x. For example, the following code shows that the signed number x =−43 equals the unsigned number y =2^32 −43:

5)More generally, x is divisible by 2^k exactly when x & (2^k −1) = 0.
