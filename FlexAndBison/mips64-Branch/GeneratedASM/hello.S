    .abicalls
    .text
    .globl main
    .ent main
main:
    .frame $sp, 32, $ra
    .mask 0x80000000, -4
    .set noreorder
    daddiu  $sp, $sp, -32
    sd      $ra, 24($sp)

    dla     $a0, msg        # $a0 = pointer to string
    jal     printf

    ld      $ra, 24($sp)
    daddiu  $sp, $sp, 32
    li      $v0, 0
    jr      $ra
    .end main

    .data
msg:
    .asciiz "Hello from MIPS64!\n"

    .extern printf

