int fib_local(int n) {
    int result;
    if (n <= 1) {
        result = n;
    } else {
        result = fib_local(n - 1) + fib_local(n - 2);
    }
    return result;
}

int main() {
    return fib_local(10);
}

