.data 
arr1: .word 20, 10, 5, 2, 8
arr2: .word 14, 3, 5, 6, 1
arr3: .space 20   # 20 bytes for 5 integers
.text
.globl main
main:
    la $a0, arr1   # array 1
    la $a1, arr2   # array 2
    li $a2, 5      # length of both arrays
    li $t0, 0      # index (i = 0)
multarray:
    # figure out how much space to allocate for frame
    # 4*2*length = 40 so need 64 bytes
    addiu $sp, $sp, -64
    sw $ra, 60($sp)
    sw $fp, 56($sp)
    addiu $fp, $sp, 64
    jal loop
loop:
    slt $t1, $t0, $a2     # $t1 is 1 if i < length
    beq $t1, $zero, done  # if i >= length then exit loop
    sll $t2, $t0, 2       # $t2 = i*4
    add $t3, $t2, a0      # $t3 = arr1 + i*4
    add $t4, $t2, a1      # $t4 = arr2 + i*4
    lw $t5, 0($t3)        # $t5 = arr1[i]
    lw $t6, 0($t4)        # $t6 = arr2[i]
    # need to put these values in $a0 and $a1 
done:
    jr $ra
mult32:
    mult $a0, $a1
    mfhi $v0
    mflo $v1
    jr $ra
