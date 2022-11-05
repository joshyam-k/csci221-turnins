.text
.globl main
main:
    li $t0, 0   # three values stored in ascending order (t0 < t1 < t2)
    li $t1, 0
    li $t2, 0
    li $s0, 0   # number of values x s.t, x < t0
    li $s1, 0   # number of values x s.t, x > t2
    li $s2, 0   # number of values x s.t, t0 <= x < t1
    li $s3, 0   # number of values x s.t, t1 <= x < t2
    # array is stored in a0 and length stored in a1
    li $t3, 0   # index of array
loop_smaller:
    slt $t4, $t3, $a1   # $t4 = (i < length)
    beq $t4, $zero, Exit
    addi $t3, $t3, 1    # i++
    sll $t5, $t3, 2     # offset: $t5 = 4*i
    add $t6, $a0, $t5   # $t6 = a0 + 4*i
    lw $t7, 0($t6)      # $t7 = a[i]
    slt $t8, $t0, $t7   # $t8 = ($t0 < a[i])
    beq $t8, $zero, loop_smaller    # if $t0 > a[i] we jump back to top of loop
    addi $s0, $s0, 1        # count++
    j loop_smaller          # return to top of loop
reset_reg:
    add $t3, $zero, $zero   # clear some temporary registers
    add $t4, $zero, $zero  
    add $t5, $zero, $zero
    add $t6, $zero, $zero
    add $t7, $zero, $zero
    add $t8, $zero, $zero
loop_larger:
    slt $t4, $t3, $a1   # (i < length)
    beq $t4, $zero, Exit
    addi $t3, $t3, 1    # i++
    sll $t5, $t3, 2     # t5 = 4*i
    add $t6, $a0, $t5   # a0 + 4*i
    lw $t7, 0($t6)      # t7 = a[i]
    slt $t8, $t2, $t7   # checking (a[i] > t2) as (t2  < a[i] != 0)
    beq $t8, $zero, loop_larger    # if (a[i] > t2) is false then jump to next iteration
    addi $s1, $s1, 1    # count++
    j loop_larger

    
