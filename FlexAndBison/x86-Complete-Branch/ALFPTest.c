void test (int a, int b, int c) {
    int d = a+b+c;

    return;
}

int fib_local(int n) {
    int result;
    if (n <= 1) {
        result = n;
    } else {
        result = fib_local(n - 1) + fib_local(n - 2);
    }
    return result;
}

int fib_n(int n) {
    int result;
    
    if (n <= 1) {
        result = n;
    } else {
        result = fib_n(n - 1) + fib_n(n - 2);
    }
    return result;
}


int fib_void(void) {
    int n = 14;
    if (n <= 1)
        return n;
    return fib_n(n);
}


int sum4(int a, int b, int c, int d) {
    return a + b + c + d;
}


int main(void) {
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
        else if (x != 4) {
            x = x + 2;
            x = x*4;
        }
        else if (x >= 5 && z != 0) 
            y = y + 1;
        else 
            z = z | x;
    }
    
    int fib =fib_local(20);
    int fib2 = fib_void();
    int sum = sum4(a, b, c, d);
    /* Add switch-style behavior using if-chains (if no switch)*/
    int cond = (z ^ y) & 7;
    if (cond == 0) a = a+ 1;
    else if (cond == 1) a = a + 2;
    else if (cond == 2) a = a +  3;
    else if (cond == 3) a = a + 4;
    else if (cond == 4) a = a + 5;
    else a = a + 6;

    test(a, c, x);
    if (x >= 0 || (y>=0 && z>=0))
        sum = sum+1;

    // Final return combines many variables
    return (x + y + z + a + b + c + d + e + fib+ fib2 + sum);
}



