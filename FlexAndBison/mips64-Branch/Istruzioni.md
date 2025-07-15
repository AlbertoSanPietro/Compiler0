## Prerequisites

```
sudo apt update
sudo apt install \
  binutils-mips64-linux-gnuabi64 \
  gcc-mips64-linux-gnuabi64 \
  qemu-user \
  qemu-user-static \
  qemu-system-mips
```

## Assemble
```
mips64-linux-gnuabi64-as -o test.o test.asm
```

## Link
```
mips64-linux-gnuabi64-ld -o test test.o
```

## Run
```
qemu-mips64 ./test
```



