int main() {
    int x = 2;
    int y = x >> 1;

    int z = (5 & 3) | (1 ^ (7 << 2));

    int a = 0;
    if (x == 2) a = a + 1;

    return x + y + z + a;
}

