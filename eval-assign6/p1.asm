.text
.globl main
main: 

decay:
    addiu $sp, $sp, -32
    sw $ra, 28($sp)
    sw $fp, 24($sp)
    addiu $fp, $sp, 32
    li $t0, 0   # total initialized to zero
    li $t1, 1   # index initialized to one
    la $a0, $s0 # $a0 is the first address of the array of values
    li $a1, 5   # length
    li $a2, 2   # decay
    jal decay_t
    lw $fp, 24($sp)
    lw $sp, 28($sp)
    addiu $sp, $sp, 32
    jr $ra
decay_t:
    addiu $sp, $sp, -32
    sw $ra 28($sp)
    sw $fp 24($sp)
    addiu $fp, $sp, 32
    slt $t3, $a1, $t1   # 1 if length < i
    bne $t3, $zero, Exit
    jal pow
    lw $fp, 24($sp)
    lw $sp, 28($sp)
    addiu $sp, $sp, 32
    # need to get values[length - i]
    sub $t4, $a1, $t1
    sll $t4, $t4, 2
    add $t4, $t4, $a0
    lw $t5, 0($t4)
    div $v0, $t5
    add $t0, $t0, $mflo
    addi $t1, $t1, 1
    j decay_t
# assume x is in $a0, and y is in $a1
pow: 
    addiu $sp, $sp, -4   # allocate space
    sw $ra, 0($sp)      # store the return address
    bne $a1, $zero, switch1
    li $v0 1            # if y is zero we should just return 1
    j return
switch1:
    andi $t0, $a1, 1    # checking parity
    bne $t0, $zer, switch2  # if odd go to switch2
    srl $a0, $a0, 1
    jal pow
    mul $v0, $v0, $v0       
    j return
switch2:
    addi $a0, $a0, -1
    jal pow
    mul $v0, $a0, $v0
return:
    lw $ra 0($sp)       # restore ra
    addi $sp, $sp, 4    # pop frame
    jr $ra
Exit:
    lw $v0, 0($t0) 
    jr $ra
