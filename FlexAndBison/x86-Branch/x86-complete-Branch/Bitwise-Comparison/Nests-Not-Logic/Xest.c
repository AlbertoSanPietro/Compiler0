int main() {
    int x = 2;
    int y = x >> 1; // Right shift test

    int z1 = 5 & 3;
    int z2 = 1 ^ (7 << 2);
    int z = z1 | z2; // Bitwise with precedence isolated

    int a = 0;
    int b = -1;
    int c = ~a;
    int d = ~b;
    int e1 = x & 3;
    int e2 = y ^ 2;
    int e = (e1 | e2) << 1;

    if (x == 2) a = a + 1;
    if (x != 0) a = a + 2;
    if (x >= 2) a = a + 4;
    if (x <= 2) a = a + 8;
    if (x >  1) a = a + 16;
    if (x <  3) a = a + 32;

    while (x <= 10) {
        if (x % 2 == 0) {
            x = x << 1;
        } else {
            if (x != 4) {
                x = x + 2;
            } else {
                if (x >= 5) {
                    y = y + 1;
                } else {
                    z = z | x;
                }
            }
        }
    }

    int cond = (z ^ y) & 7;
    if (cond == 0) {
        a = a + 1;
    } else {
        if (cond == 1) {
            a = a + 2;
        } else {
            if (cond == 2) {
                a = a + 3;
            } else {
                if (cond == 3) {
                    a = a + 4;
                } else {
                    if (cond == 4) {
                        a = a + 5;
                    } else {
                        a = a + 6;
                    }
                }
            }
        }
    }

    // Additional tests

    int g = x + 1;
    if (g > 2) {
        g = g + 10;
    }

    int h = 0;
    if (x < 100) {
        if ((x & 1) != 0) {
            if (x == 64) {
                h = h + 1;
            }
        }
    }

    int i1 = ~(x & 3);
    int i2 = ~(y | 1);
    int i = i1 + i2;

    int neg = -16;
    int j = neg >> 2;

    int t1 = (1 ^ 2) & 3;
    int t2 = 4 ^ 5;
    int k = t1 | t2;

    int sum = g + h + i + j + k;
    int m = (sum & 255) | 7;

    return x + y + z + a + b + c + d + e + g + h + i + j + k + m;
}

