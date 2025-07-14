.ORIG x3000
    AND R0, R0, #0
    ADD R0, R0, #2
    ST R0, VAR0
    AND R0, R0, #0
    ADD R0, R0, #5
    NOT R0, R0
    ADD R0, R0, #1
    ST R0, VAR1
L0:
    LD R0, VAR0
    STR R0, TMP
    AND R0, R0, #0
    ADD R0, R0, #10
    LDR R1, TMP
    NOT R0, R0
    ADD R0, R0, #1
    ADD R2, R1, R0
    BRn TRUE2
    AND R0, R0, #0
    BR DONE2
TRUE2:
    AND R0, R0, #0
    ADD R0, R0, #1
DONE2:
    BRz L1
    LD R0, VAR0
    STR R0, TMP
    AND R0, R0, #0
    ADD R0, R0, #2
    LDR R1, TMP
    STR R0, MODDIV
    STR R1, MODSRC
MODLOOP5:
    LDR R0, MODSRC
    LDR R1, MODDIV
    NOT R1, R1
    ADD R1, R1, #1
    ADD R2, R0, R1
    BRn MODEND6
    STR R2, MODSRC
    BR MODLOOP5
MODEND6:
    LDR R0, MODSRC
    STR R0, TMP
    AND R0, R0, #0
    ADD R0, R0, #0
    LDR R1, TMP
    NOT R2, R0
    ADD R2, R2, #1
    ADD R2, R2, R1
    BRz TRUE8
    AND R0, R0, #0
    BR DONE8
TRUE8:
    AND R0, R0, #0
    ADD R0, R0, #1
DONE8:
    BRz L3
    LD R0, VAR0
    STR R0, TMP
    AND R0, R0, #0
    ADD R0, R0, #1
    LDR R1, TMP
    ADD R0, R1, R0
    ST R0, VAR0
    BR L4
L3:
    LD R0, VAR0
    STR R0, TMP
    AND R0, R0, #0
    ADD R0, R0, #2
    LDR R1, TMP
    ADD R0, R1, R0
    ST R0, VAR0
L4:
    BR L0
L1:
    LD R0, VAR0
    STR R0, TMP
    LD R0, VAR1
    LDR R1, TMP
    ADD R0, R1, R0
    HALT
    HALT
VAR0 .FILL #0
VAR1 .FILL #0
TMP .BLKW 1
MODSRC .BLKW 1
MODDIV .BLKW 1
.END
