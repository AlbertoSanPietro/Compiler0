int main() {
    int x = 2;
    int y = x >> 1;
    int z = 5 & 3 | 1 ^ 7 << 2;

    int a = 0;
    int b = -1;
    int c = ~a;
    int d = ~(b);
    int e = ((x & 3) | (y ^ 2)) << 1;

    if (x == 2) {
        int scoped1 = 10;
        a = a + scoped1;
    }

    if (x != 0) {
        int scoped2 = 20;
        a = a + scoped2;
    }

    if (x >= 2) {
        int x = 100;  // Shadow outer x
        a = a + (x >> 2);  // Should use inner x (100 >> 2 = 25)
    }

    if (x <= 2) {
        int a = 1;  // Shadow outer a
        a = a + 5;  // Modify shadowed a (should not affect outer a)
    }

    // Outer 'a' should still be intact
    if (x > 1) {
        a = a + 1;
    }

    while (x <= 4) {
        int scoped_loop = x * 2;
        x = x + 1;
        a = a + scoped_loop;
    }

    // More nested scoping
    if (x > 4) {
        if (x < 100) {
            int temp = 3;
            y = y + temp;
        }
    }

    // Final calculation
    int cond = (z ^ y) & 7;
    if (cond == 0) a = a+ 1;
    else if (cond == 1) a = a + 2;
    else if (cond == 2) a = a + 3;
    else if (cond == 3) a = a + 4;
    else if (cond == 4) a = a + 5;
    else a = a + 6;

    int g = 0;
    if ((g = x + 1) > 2) {
        int local = g;
        g = g + local;
    }

    int h = 0;
    if (x < 100) {
        if (x & 1) {
            if (x == 64) {
                int deep = 42;
                h = h + deep;
            }
        }
    }

    int i = ~(x & 3) + (~(y | 1));
    int j = -16 >> 2;
    int k = (1 ^ 2) & 3 | 4 ^ 5;
    int m = (g + h + i + j + k) & 255 | 7;

    return x + y + z + a + b + c + d + e + g + h + i + j + k + m;
}

