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
    jal decay_t
decay_t:
# will need to compute x^y in the function
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
