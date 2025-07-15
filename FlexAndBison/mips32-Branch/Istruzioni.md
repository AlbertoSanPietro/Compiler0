## Prerequisites

```
sudo apt update
sudo apt install \
  binutils-mips-linux-gnu \
  gcc-mips-linux-gnu \
  qemu-user \
  qemu-user-static \
  qemu-system-mips

```

## Assemble
```
mips-linux-gnu-as -o test.o test.asm 
```

## Link

```
mips-linux-gnu-ld -o test test.o
```

## Run
```
qemu-mips ./test
```


