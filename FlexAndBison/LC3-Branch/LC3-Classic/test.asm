.ORIG x3000
    AND R0, R0, #0
    ADD R0, R0, #2
    ST R0, VAR0
L0:
    LD R0, VAR0
    ST R0, TMP
    AND R0, R0, #0
    ADD R0, R0, #10
    LD R1, TMP
    NOT R2, R0
    ADD R2, R2, #1
    ADD R2, R1, R2
    BRn TRUE2
    AND R0, R0, #0
    BR DONE2
TRUE2:
    AND R0, R0, #0
    ADD R0, R0, #1
DONE2:
    BRz L1
    LD R0, VAR0
    ST R0, TMP
    AND R0, R0, #0
    ADD R0, R0, #2
    LD R1, TMP
    ; operation '%' not directly supported in LC3
    ST R0, TMP
    AND R0, R0, #0
    ADD R0, R0, #0
    LD R1, TMP
    NOT R2, R0
    ADD R2, R2, #1
    ADD R2, R2, R1
    BRz TRUE5
    AND R0, R0, #0
    BR DONE5
TRUE5:
    AND R0, R0, #0
    ADD R0, R0, #1
DONE5:
    BRz L3
    LD R0, VAR0
    ST R0, TMP
    AND R0, R0, #0
    ADD R0, R0, #1
    LD R1, TMP
    ADD R0, R1, R0
    ST R0, VAR0
    BR L4
L3:
    LD R0, VAR0
    ST R0, TMP
    AND R0, R0, #0
    ADD R0, R0, #2
    LD R1, TMP
    ADD R0, R1, R0
    ST R0, VAR0
L4:
    BR L0
L1:
    LD R0, VAR0
    HALT
    HALT
VAR0 .FILL #0
TMP .BLKW 1
.END
