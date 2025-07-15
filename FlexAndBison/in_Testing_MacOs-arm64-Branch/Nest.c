int main() {
    int x = 2;
    int y = -5;
    while (x < 10) {
        if (x % 2 == 0)
            x = x + 1;
        else
            x = x + 2;
    }
    return x+y;
}

