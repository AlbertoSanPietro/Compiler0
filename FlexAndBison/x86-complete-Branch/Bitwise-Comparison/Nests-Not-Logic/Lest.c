int main()  {
    int x = 2;
    int y = x >> 1;                   // Right shift test
    int z = 5 & 3 | 1 ^ 7 << 2;       // Bitwise precedence test

    int a = 0;
    int b = -1;
    int c = ~a;
    int d = ~(b);
    int e = ((x & 3) | (y ^ 2)) << 1; // Compound bitwise ops

    if (x == 2) a = a + 1;
    if (x != 0) a = a + 2;
    if (x >= 2) a = a + 4;
    if (x <= 2) a = a + 8;
    if (x >  1) a = a + 16;
    if (x <  3) a = a + 32;

    // Mix in some loops
    while (x <= 10) {
        if (x % 2 == 0)
            x = x << 1;
        else if (x != 4)
            x = x + 2;
        else if (x >= 5) 
            y = y + 1;
        else 
            z = z | x;
    }

    // Add switch-style behavior using if-chains (if no switch)
    int cond = (z ^ y) & 7;
    if (cond == 0) a = a+ 1;
    else if (cond == 1) a = a + 2;
    else if (cond == 2) a = a +  3;
    else if (cond == 3) a = a + 4;
    else if (cond == 4) a = a + 5;
    else a = a + 6;

    // === Additional Test Cases ===

    // f: Multiple unary operators in one expression
    //int f = ~-~x;

    // g: Side-effect in condition
    int g = 0;
    if ((g = x + 1) > 2) g = g + 10;

    // h: Nested ifs
    int h = 0;
    if (x < 100) {
        if (x & 1) {
            if (x == 64)
                h = h + 1;
        }
    }

    // i: Mixing more unary and binary
    int i = ~(x & 3) + (~(y | 1));

    // j: Right shift and negative numbers
    int j = -16 >> 2;

    // k: Chain of bitwise ops
    int k = (1 ^ 2) & 3 | 4 ^ 5;

    // m: Combining all
    int m = ((g + h + i + j + k) & 255) | 7;

    // Final return combines all
    return (x + y + z + a + b + c + d + e + g + h + i + j + k + m);
}

