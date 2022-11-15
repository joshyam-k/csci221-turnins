.data 
arr1: .word 20, 10, 5, 2, 8
arr2: .word 14, 3, 5, 6, 1
arr3: .space 40   # 40 bytes for 5 64 bit integers
.text
.globl main
main:
    la $a0, arr1   # array 1
    la $a1, arr2   # array 2
    li $a2, 5      # length of all arrays
    la $a3, arr3   # empty array to be filled
    li $t0, 0      # index (i = 0)
# need to figure out how much space to allocate for multarray
multarray:
    addiu $sp, $sp, -32   # allocate space for frame 
    sw $ra, 28($sp)       # store return address and frame pointer
    sw $fp, 24($sp)
    addiu $fp, $sp, 32    # set new frame pointer
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
    sll $t7, $t0, 3       # $t7 = i*8
    add $t8, $a3, $t7     # $t8 = arr3 + i*8
    add $t9, $a3, $t2     # $t9 = arr3 + i*4
    sw $v0 0($t8)         
    sw $v1 0($t9)
    lw $a0, 20($sp)       # restore array addresses
    lw $a1, 16($sp)        
    lw $fp 24($sp)        # restore fp and ra
    lw $ra 28($sp)
    addi $t0, $t0, 1      # i++
    addiu $sp, $sp, 32    # pop frame
    j multarray           # return back to top of loop 
done:
    jr $ra
mult32:
    mult $a0, $a1
    mfhi $v0
    mflo $v1
    jr $ra
