int main() {
    int a = 0;
    int b = 1;
    int x = a && b;
    int y = a || b;
    int z = !a;
    return x + y + z;  // Expected: 0 + 1 + 1 = 2
}

