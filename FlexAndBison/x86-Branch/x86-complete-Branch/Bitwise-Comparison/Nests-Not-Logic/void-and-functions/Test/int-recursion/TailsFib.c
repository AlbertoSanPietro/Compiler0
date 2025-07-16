int fib_tail(int n, int a, int b) {
    if (n == 0) return a;
    return fib_tail(n - 1, b, a + b);
}

int main() {
    return fib_tail(10, 0, 1);
}

