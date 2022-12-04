.text
.globl main
main:
    # array, permutations, and length are stored in $a0-$a2 respectively
    li $t0, 0   # index (i = 0)
loop:
    slt $t1, $t0, $a2   # (i < length)
    beq $t1, $zero, Exit   # if i < length is false then exit the loop
    # need to get array[i] address and array[permutation[i]] address
    # get permutation[i] value first
    sll $t2, $t0, 2     # t2 = 4*i
    add $t3, $a1, $t2   # t3 = a1 + 4*i
    lw $t4, 0($t3)      # t4 = a1[i]
    # now get array[permutation[i]]
    sll $t5, $t4, 2     # a1[i]*4
    add $t6, $a0, $t5   # t6 = a0 + a1[i]*4
    lw $t7, 0($t6)      # t7 = array[permutation[i]]
    # now get array[i]
    add $t8, $a0, $t2   # t8 = a0 + 4*i
    lw $t9, 0($t8)      # t9 = a[i]
    # now swap
    sw $t9 0($t6)       # array[permutation[i]] = array[i]
    sw $t7 0($t8)       # array[i] = array[permutation[i]]
    addi $t0, $t0, 1    # i++
    j loop              # return to top of loop
Exit:
    li $v0, 10
    syscall
    
