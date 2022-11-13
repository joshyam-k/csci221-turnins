.data 
arr1: .word 20, 10, 5, 2, 8
arr2: .word 14, 3, 5, 6, 1
arr3: .space 40   # 20 bytes for 5 64 bit integers
.text
.globl main
main:
    la $a0, arr1   # array 1
    la $a1, arr2   # array 2
    li $a2, 5      # length of allh arrays
    la $a3, arr3   # empty array to be filled
    li $t0, 0      # index (i = 0)
# need to figure out how much space to allocate for multarray and loop
# need to 
multarray:
    # figure out how much space to allocate for frame
    # 4*2*length*2 = 80
    addiu $sp, $sp, -96
    sw $ra, 92($sp)
    sw $fp, 88($sp)
    addiu $fp, $sp, 96
    jal loop
loop:
    addiu $sp, $sp, -32
    sw $ra, 28($sp)
    sw $fp, 24($sp)
    addiu $fp, $sp, 32
    slt $t1, $t0, $a2     # $t1 is 1 if i < length
    beq $t1, $zero, done  # if i >= length then exit loop
    sll $t2, $t0, 2       # $t2 = i*4
    add $t3, $t2, a0      # $t3 = arr1 + i*4
    add $t4, $t2, a1      # $t4 = arr2 + i*4
    lw $t5, 0($t3)        # $t5 = arr1[i]
    lw $t6, 0($t4)        # $t6 = arr2[i]
    # need to put these values in $a0 and $a1
    # so first we store the array addresses since we will need them in future loop iterations
    sw $a0 20($sp)
    sw $a1 16($sp)
    add $a0, $zero, $t5   # $a0 = arr1[i]
    add $a1, $zero, $t6   # $a1 = arr2[i]
    jal mult32
    # place $v0 and $v1 in order in the empty arr3
    lw $a0, 20($sp)       # restore array addresses
    lw $a1, 16($sp)         
    $t0
    addiu $sp, $sp, 32    # pop frame
    j loop                # return back to top of loop 
done:
    jr $ra
mult32:
    mult $a0, $a1
    mfhi $v0
    mflo $v1
    jr $ra
