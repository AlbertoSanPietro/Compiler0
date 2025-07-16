int main() {
    int x = 2;
    
    int y= x >> 1;

    int z = 5 & 3 | 1 ^ 7 << 2;

    while (x <= 10) {
        if (x % 2 == 0)
            x = x << 1;
        else if (x != 4)
            x = x + 2;
        else if (x >=5) 
            y = y+1;
        else 
            z= z | x;

    }
    return (x+z+y);
}

