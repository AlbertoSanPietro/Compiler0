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
mips64-linux-gnuabi64-as test.asm -o test.o 
```

## Link
```
mips64-linux-gnuabi64-ld -static test.o -o test
```

## Run
```
qemu-mips64 ./test
```
OR:
```
qemu-mips64 test
```



